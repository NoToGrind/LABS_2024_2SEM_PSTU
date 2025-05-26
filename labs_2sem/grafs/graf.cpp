#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <limits>
#include <algorithm>
#include <SFML/Graphics.hpp>

class Graph {
private:
    // Структура для хранения информации о ребре
    struct Edge {
        int to;         // Индекс вершины, куда ведет ребро
        float weight;   // Вес ребра
        Edge(int t, float w) : to(t), weight(w) {}
    };

    std::vector<std::vector<Edge>> adjacencyList;  // Список смежности
    std::vector<sf::Vector2f> nodePositions;       // Позиции вершин для отрисовки
    std::vector<std::pair<int, int>> edges;        // Список всех ребер
    std::vector<float> edgeWeights;                // Веса всех ребер

public:
    Graph() = default;

    // Добавление новой вершины в граф
    void addNode(float x, float y) {
        adjacencyList.emplace_back();          // Добавляем пустой список смежности
        nodePositions.emplace_back(x, y);      // Запоминаем позицию вершины
    }

    // Удаление вершины из графа
    void removeNode(int index) {
        if (index < 0 || index >= adjacencyList.size()) return;

        // Удаляем все ребра, связанные с этой вершиной
        for (auto& list : adjacencyList) {
            list.erase(std::remove_if(list.begin(), list.end(), 
                     [index](const Edge& e) { return e.to == index; }), list.end());
        }

        // Удаляем саму вершину
        adjacencyList.erase(adjacencyList.begin() + index);
        nodePositions.erase(nodePositions.begin() + index);

        // Обновляем индексы в списках смежности
        for (auto& list : adjacencyList) {
            for (auto& edge : list) {
                if (edge.to > index) edge.to--;
            }
        }

        // Обновляем список ребер
        edges.erase(std::remove_if(edges.begin(), edges.end(), 
                  [index](const std::pair<int, int>& e) { 
                      return e.first == index || e.second == index; 
                  }), edges.end());

        // Обновляем индексы в списке ребер
        for (auto& edge : edges) {
            if (edge.first > index) edge.first--;
            if (edge.second > index) edge.second--;
        }
    }

    // Добавление ребра между вершинами
    void addEdge(int from, int to, float weight) {
        if (from < 0 || from >= adjacencyList.size() || 
            to < 0 || to >= adjacencyList.size()) return;

        // Добавляем ребро в обе стороны (граф неориентированный)
        adjacencyList[from].emplace_back(to, weight);
        adjacencyList[to].emplace_back(from, weight);
        edges.emplace_back(from, to);
        edgeWeights.push_back(weight);
    }

    // Удаление ребра между вершинами
    void removeEdge(int from, int to) {
        if (from < 0 || from >= adjacencyList.size() || 
            to < 0 || to >= adjacencyList.size()) return;

        // Удаляем ребро из списка смежности первой вершины
        adjacencyList[from].erase(std::remove_if(adjacencyList[from].begin(), 
                                 adjacencyList[from].end(), 
                                 [to](const Edge& e) { return e.to == to; }), 
                                 adjacencyList[from].end());

        // Удаляем ребро из списка смежности второй вершины
        adjacencyList[to].erase(std::remove_if(adjacencyList[to].begin(), 
                               adjacencyList[to].end(), 
                               [from](const Edge& e) { return e.to == from; }), 
                               adjacencyList[to].end());

        // Ищем и удаляем ребро из списка ребер
        auto it = std::find(edges.begin(), edges.end(), std::make_pair(from, to));
        if (it != edges.end()) {
            size_t index = it - edges.begin();
            edges.erase(it);
            edgeWeights.erase(edgeWeights.begin() + index);
            return;
        }

        // Проверяем обратное направление (так как граф неориентированный)
        it = std::find(edges.begin(), edges.end(), std::make_pair(to, from));
        if (it != edges.end()) {
            size_t index = it - edges.begin();
            edges.erase(it);
            edgeWeights.erase(edgeWeights.begin() + index);
        }
    }

    // Обновление веса ребра
    void updateEdgeWeight(int from, int to, float newWeight) {
        if (from < 0 || from >= adjacencyList.size() || 
            to < 0 || to >= adjacencyList.size()) return;

        // Обновляем вес в списке смежности первой вершины
        for (auto& edge : adjacencyList[from]) {
            if (edge.to == to) {
                edge.weight = newWeight;
                break;
            }
        }

        // Обновляем вес в списке смежности второй вершины
        for (auto& edge : adjacencyList[to]) {
            if (edge.to == from) {
                edge.weight = newWeight;
                break;
            }
        }

        // Обновляем вес в списке ребер
        auto it = std::find(edges.begin(), edges.end(), std::make_pair(from, to));
        if (it != edges.end()) {
            size_t index = it - edges.begin();
            edgeWeights[index] = newWeight;
            return;
        }

        // Проверяем обратное направление
        it = std::find(edges.begin(), edges.end(), std::make_pair(to, from));
        if (it != edges.end()) {
            size_t index = it - edges.begin();
            edgeWeights[index] = newWeight;
        }
    }

    // Алгоритм обхода в ширину (BFS)
    std::vector<int> breadthFirstSearch(int start) {
        std::vector<int> traversal;  // Результат обхода
        if (adjacencyList.empty()) return traversal;

        std::vector<bool> visited(adjacencyList.size(), false);  // Посещенные вершины
        std::queue<int> q;  // Очередь для BFS

        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            traversal.push_back(current);

            // Добавляем все смежные непосещенные вершины в очередь
            for (const auto& edge : adjacencyList[current]) {
                if (!visited[edge.to]) {
                    visited[edge.to] = true;
                    q.push(edge.to);
                }
            }
        }

        return traversal;
    }

    // Алгоритм обхода в глубину (DFS)
    std::vector<int> depthFirstSearch(int start) {
        std::vector<int> traversal;  // Результат обхода
        if (adjacencyList.empty()) return traversal;

        std::vector<bool> visited(adjacencyList.size(), false);  // Посещенные вершины
        std::stack<int> s;  // Стек для DFS

        s.push(start);
        visited[start] = true;

        while (!s.empty()) {
            int current = s.top();
            s.pop();
            traversal.push_back(current);

            // Добавляем все смежные непосещенные вершины в стек
            for (const auto& edge : adjacencyList[current]) {
                if (!visited[edge.to]) {
                    visited[edge.to] = true;
                    s.push(edge.to);
                }
            }
        }

        return traversal;
    }

    // Алгоритм Дейкстры для поиска кратчайших путей
    std::vector<float> dijkstra(int start) {
        // Инициализируем расстояния бесконечностью
        std::vector<float> distances(adjacencyList.size(), std::numeric_limits<float>::max());
        if (adjacencyList.empty()) return distances;

        distances[start] = 0;  // Расстояние до стартовой вершины = 0
        std::set<std::pair<float, int>> pq;  // Приоритетная очередь
        
        pq.insert({0, start});

        while (!pq.empty()) {
            int current = pq.begin()->second;
            pq.erase(pq.begin());

            // Обновляем расстояния до соседей
            for (const auto& edge : adjacencyList[current]) {
                if (distances[edge.to] > distances[current] + edge.weight) {
                    pq.erase({distances[edge.to], edge.to});
                    distances[edge.to] = distances[current] + edge.weight;
                    pq.insert({distances[edge.to], edge.to});
                }
            }
        }

        return distances;
    }

    // Отрисовка графа в окне SFML
    void draw(sf::RenderWindow& window) {
        // Загружаем шрифт для подписей
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Ошибка загрузки шрифта" << std::endl;
            return;
        }

        // Отрисовываем все ребра
        for (size_t i = 0; i < edges.size(); ++i) {
            const auto& edge = edges[i];
            sf::Vector2f from = nodePositions[edge.first];
            sf::Vector2f to = nodePositions[edge.second];

            // Линия ребра
            sf::Vertex line[] = {
                sf::Vertex(from, sf::Color::Black),
                sf::Vertex(to, sf::Color::Black)
            };
            window.draw(line, 2, sf::Lines);

            // Подпись с весом ребра
            sf::Text weightText(std::to_string(edgeWeights[i]), font, 16);
            weightText.setFillColor(sf::Color::Red);
            weightText.setPosition((from.x + to.x) / 2, (from.y + to.y) / 2);
            window.draw(weightText);
        }

        // Отрисовываем все вершины
        for (size_t i = 0; i < nodePositions.size(); ++i) {
            // Круг, представляющий вершину
            sf::CircleShape circle(20);
            circle.setFillColor(sf::Color::Green);
            circle.setPosition(nodePositions[i].x - 20, nodePositions[i].y - 20);
            circle.setOutlineThickness(2);
            circle.setOutlineColor(sf::Color::Black);
            window.draw(circle);

            // Подпись вершины (ее индекс)
            sf::Text nodeText(std::to_string(i), font, 16);
            nodeText.setFillColor(sf::Color::Black);
            nodeText.setPosition(nodePositions[i].x - 5, nodePositions[i].y - 10);
            window.draw(nodeText);
        }
    }

    // Геттеры для доступа к данным графа
    size_t getNodeCount() const { return nodePositions.size(); }
    const std::vector<std::pair<int, int>>& getEdges() const { return edges; }
    const std::vector<sf::Vector2f>& getNodePositions() const { return nodePositions; }

    // Установка позиции вершины
    void setNodePosition(int index, float x, float y) {
        if (index >= 0 && index < nodePositions.size()) {
            nodePositions[index] = sf::Vector2f(x, y);
        }
    }

    // Вывод матрицы смежности в консоль
    void printAdjacencyMatrix() {
        size_t n = adjacencyList.size();
        std::vector<std::vector<float>> matrix(n, std::vector<float>(n, 0));

        // Заполняем матрицу смежности
        for (size_t i = 0; i < n; ++i) {
            for (const auto& edge : adjacencyList[i]) {
                matrix[i][edge.to] = edge.weight;
            }
        }

        // Выводим матрицу
        std::cout << "Матрица смежности:\n";
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
};

// Класс для визуального редактирования графа
class GraphEditor {
private:
    Graph graph;                    // Наш граф
    sf::RenderWindow window;        // Окно SFML
    int selectedNode = -1;          // Выбранная вершина
    bool addingEdge = false;        // Режим добавления ребра
    int edgeStart = -1;             // Первая вершина для добавляемого ребра
    bool movingNode = false;        // Флаг перемещения вершины

public:
    GraphEditor() : window(sf::VideoMode(800, 600), "Редактор графов") {
        // Создаем начальный граф с 6 вершинами
        for (int i = 0; i < 6; ++i) {
            // Располагаем вершины по кругу
            float x = 400 + 150 * cos(2 * 3.14159 * i / 6);
            float y = 300 + 150 * sin(2 * 3.14159 * i / 6);
            graph.addNode(x, y);
        }

        // Добавляем ребра между вершинами
        graph.addEdge(0, 1, 1);
        graph.addEdge(1, 2, 2);
        graph.addEdge(2, 3, 3);
        graph.addEdge(3, 4, 4);
        graph.addEdge(4, 5, 5);
        graph.addEdge(5, 0, 6);
        graph.addEdge(0, 2, 7);
        graph.addEdge(1, 3, 8);
    }

    // Главный цикл приложения
    void run() {
        while (window.isOpen()) {
            handleEvents();  // Обработка событий
            update();        // Обновление состояния
            render();        // Отрисовка
        }
    }

private:
    // Обработка событий
    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Обработка нажатий кнопок мыши
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    handleLeftClick(event.mouseButton.x, event.mouseButton.y);
                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    handleRightClick(event.mouseButton.x, event.mouseButton.y);
                }
            }

            // Обработка отпускания кнопки мыши
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    movingNode = false;
                }
            }

            // Обработка нажатий клавиш
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::B) {
                    // Выполнение BFS
                    if (selectedNode != -1) {
                        auto traversal = graph.breadthFirstSearch(selectedNode);
                        std::cout << "BFS начиная с вершины " << selectedNode << ": ";
                        for (int node : traversal) std::cout << node << " ";
                        std::cout << std::endl;
                    }
                } else if (event.key.code == sf::Keyboard::D) {
                    // Выполнение DFS
                    if (selectedNode != -1) {
                        auto traversal = graph.depthFirstSearch(selectedNode);
                        std::cout << "DFS начиная с вершины " << selectedNode << ": ";
                        for (int node : traversal) std::cout << node << " ";
                        std::cout << std::endl;
                    }
                } else if (event.key.code == sf::Keyboard::J) {
                    // Выполнение алгоритма Дейкстры
                    if (selectedNode != -1) {
                        auto distances = graph.dijkstra(selectedNode);
                        std::cout << "Дейкстра начиная с вершины " << selectedNode << ":\n";
                        for (size_t i = 0; i < distances.size(); ++i) {
                            std::cout << "Вершина " << i << ": " << distances[i] << "\n";
                        }
                    }
                } else if (event.key.code == sf::Keyboard::A) {
                    // Переключение режима добавления ребер
                    addingEdge = !addingEdge;
                    if (addingEdge) {
                        std::cout << "Режим добавления ребер включен. Выберите первую вершину.\n";
                    } else {
                        std::cout << "Режим добавления ребер выключен.\n";
                        edgeStart = -1;
                    }
                } else if (event.key.code == sf::Keyboard::N) {
                    // Добавление новой вершины
                    graph.addNode(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                    std::cout << "Добавлена новая вершина " << (graph.getNodeCount() - 1) << std::endl;
                } else if (event.key.code == sf::Keyboard::Delete) {
                    // Удаление выбранной вершины
                    if (selectedNode != -1) {
                        graph.removeNode(selectedNode);
                        selectedNode = -1;
                        std::cout << "Вершина удалена\n";
                    }
                } else if (event.key.code == sf::Keyboard::M) {
                    // Вывод матрицы смежности
                    graph.printAdjacencyMatrix();
                }
            }
        }

        // Перемещение вершины, если она выбрана
        if (movingNode && selectedNode != -1) {
            graph.setNodePosition(selectedNode, 
                                 sf::Mouse::getPosition(window).x, 
                                 sf::Mouse::getPosition(window).y);
        }
    }

    // Обработка левого клика мыши
    void handleLeftClick(int x, int y) {
        // Проверяем, кликнули ли на вершину
        const auto& positions = graph.getNodePositions();
        for (size_t i = 0; i < positions.size(); ++i) {
            float dx = positions[i].x - x;
            float dy = positions[i].y - y;
            if (dx * dx + dy * dy <= 400) { // Проверяем попадание в круг радиусом 20px
                if (addingEdge) {
                    // Режим добавления ребра
                    if (edgeStart == -1) {
                        edgeStart = i;
                        std::cout << "Выбрана первая вершина " << i << ", теперь выберите вторую\n";
                    } else {
                        if (edgeStart != i) {
                            // Добавляем ребро со случайным весом
                            float weight = rand() % 10 + 1;
                            graph.addEdge(edgeStart, i, weight);
                            std::cout << "Добавлено ребро из " << edgeStart << " в " << i 
                                      << " с весом " << weight << std::endl;
                        }
                        edgeStart = -1;
                    }
                } else {
                    // Выбираем вершину для перемещения
                    selectedNode = i;
                    movingNode = true;
                }
                return;
            }
        }

        // Клик вне вершин - снимаем выделение
        selectedNode = -1;
    }

    // Обработка правого клика мыши
    void handleRightClick(int x, int y) {
        // Проверяем, кликнули ли на вершину
        const auto& positions = graph.getNodePositions();
        for (size_t i = 0; i < positions.size(); ++i) {
            float dx = positions[i].x - x;
            float dy = positions[i].y - y;
            if (dx * dx + dy * dy <= 400) {
                // Проверяем, кликнули ли на ребро, связанное с этой вершиной
                const auto& edges = graph.getEdges();
                for (size_t j = 0; j < edges.size(); ++j) {
                    const auto& edge = edges[j];
                    if ((edge.first == i || edge.second == i) && 
                        isPointNearLine(x, y, positions[edge.first], positions[edge.second])) {
                        // Изменяем вес ребра на случайное значение
                        float newWeight = rand() % 10 + 1;
                        graph.updateEdgeWeight(edge.first, edge.second, newWeight);
                        std::cout << "Обновлен вес ребра между " << edge.first 
                                  << " и " << edge.second << " на " << newWeight << std::endl;
                        return;
                    }
                }
                return;
            }
        }
    }

    // Проверка, находится ли точка рядом с линией
    bool isPointNearLine(int x, int y, sf::Vector2f p1, sf::Vector2f p2) {
        // Вычисляем длину отрезка
        float lineLength = sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
        // Вычисляем расстояние от точки до прямой
        float distance = abs((p2.y - p1.y) * x - (p2.x - p1.x) * y + p2.x * p1.y - p2.y * p1.x)) / lineLength;
        // Проверяем, что точка находится рядом с отрезком и в его пределах
        return distance < 10 && x >= std::min(p1.x, p2.x) - 10 && x <= std::max(p1.x, p2.x) + 10 &&
               y >= std::min(p1.y, p2.y) - 10 && y <= std::max(p1.y, p2.y) + 10;
    }

    // Обновление состояния (в данном случае не используется)
    void update() {
        // Можно добавить логику анимации или другие обновления
    }

    // Отрисовка графа и интерфейса
    void render() {
        window.clear(sf::Color::White);
        graph.draw(window);  // Отрисовываем граф

        // Отрисовываем инструкции
        sf::Font font;
        if (font.loadFromFile("arial.ttf")) {
            sf::Text instructions;
            instructions.setFont(font);
            instructions.setString(
                "Управление:\n"
                "ЛКМ: Выбрать/переместить вершину\n"
                "ПКМ на ребре: Изменить вес\n"
                "N: Добавить вершину в позиции курсора\n"
                "Delete: Удалить выбранную вершину\n"
                "A: Вкл/выкл режим добавления ребер\n"
                "B: BFS от выбранной вершины\n"
                "D: DFS от выбранной вершины\n"
                "J: Алгоритм Дейкстры от выбранной вершины\n"
                "M: Вывести матрицу смежности"
            );
            instructions.setCharacterSize(14);
            instructions.setFillColor(sf::Color::Black);
            instructions.setPosition(10, 10);
            window.draw(instructions);
        }

        window.display();
    }
};

int main() {
    GraphEditor editor;
    editor.run();
    return 0;
}