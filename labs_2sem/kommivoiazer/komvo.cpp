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
        float weight;   // Вес ребра (расстояние между городами)
        Edge(int t, float w) : to(t), weight(w) {}
    };

    std::vector<std::vector<Edge>> adjacencyList;  // Список смежности
    std::vector<sf::Vector2f> nodePositions;       // Позиции вершин для отрисовки
    std::vector<std::pair<int, int>> edges;        // Список всех ребер
    std::vector<float> edgeWeights;                // Веса всех ребер
    std::vector<std::string> cityNames;            // Названия городов

    // Вспомогательная функция для рекурсивного решения TSP
    void tspRecursive(int current, std::vector<bool>& visited, int count, 
                     float cost, float& minCost, std::vector<int>& path, 
                     std::vector<int>& bestPath) {
        // Если все города посещены и есть путь обратно в начальный город
        if (count == nodePositions.size()) {
            // Проверяем есть ли обратное ребро к начальному городу
            for (const Edge& e : adjacencyList[current]) {
                if (e.to == 0) {
                    float totalCost = cost + e.weight;
                    if (totalCost < minCost) {
                        minCost = totalCost;
                        bestPath = path;
                        bestPath.push_back(0); // Добавляем начальный город в конец
                    }
                    break;
                }
            }
            return;
        }

        // Перебираем все непосещенные города
        for (const Edge& e : adjacencyList[current]) {
            if (!visited[e.to]) {
                visited[e.to] = true;
                path[count] = e.to;
                
                tspRecursive(e.to, visited, count + 1, cost + e.weight, 
                            minCost, path, bestPath);
                
                visited[e.to] = false; // Откатываем изменения для backtracking
            }
        }
    }

public:
    Graph() = default;

    // Добавление нового города в граф
    void addNode(float x, float y, const std::string& name = "") {
        adjacencyList.emplace_back();          // Добавляем пустой список смежности
        nodePositions.emplace_back(x, y);      // Запоминаем позицию вершины
        cityNames.push_back(name.empty() ? "Город " + std::to_string(nodePositions.size()) : name);
    }

    // Удаление города из графа
    void removeNode(int index) {
        if (index < 0 || index >= adjacencyList.size()) return;

        // Удаляем все ребра, связанные с этим городом
        for (auto& list : adjacencyList) {
            list.erase(std::remove_if(list.begin(), list.end(), 
                     [index](const Edge& e) { return e.to == index; }), list.end());
        }

        // Удаляем сам город
        adjacencyList.erase(adjacencyList.begin() + index);
        nodePositions.erase(nodePositions.begin() + index);
        cityNames.erase(cityNames.begin() + index);

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

    // Добавление дороги между городами
    void addEdge(int from, int to, float weight) {
        if (from < 0 || from >= adjacencyList.size() || 
            to < 0 || to >= adjacencyList.size()) return;

        // Добавляем ребро в обе стороны (дороги двусторонние)
        adjacencyList[from].emplace_back(to, weight);
        adjacencyList[to].emplace_back(from, weight);
        edges.emplace_back(from, to);
        edgeWeights.push_back(weight);
    }

    // Решение задачи коммивояжера
    void solveTSP() {
        if (nodePositions.size() < 2) {
            std::cout << "Недостаточно городов для решения задачи коммивояжера!\n";
            return;
        }

        std::vector<bool> visited(nodePositions.size(), false);
        std::vector<int> path(nodePositions.size());
        std::vector<int> bestPath;
        float minCost = std::numeric_limits<float>::max();

        // Начинаем с первого города (индекс 0)
        visited[0] = true;
        path[0] = 0;

        tspRecursive(0, visited, 1, 0, minCost, path, bestPath);

        // Выводим результат
        if (minCost != std::numeric_limits<float>::max()) {
            std::cout << "\nОптимальный маршрут коммивояжера:\n";
            for (size_t i = 0; i < bestPath.size(); ++i) {
                std::cout << cityNames[bestPath[i]];
                if (i != bestPath.size() - 1) {
                    std::cout << " -> ";
                }
            }
            std::cout << "\nОбщая длина маршрута: " << minCost << std::endl;
        } else {
            std::cout << "Не удалось найти полный маршрут через все города!\n";
        }
    }

    // Отрисовка графа в окне SFML
    void draw(sf::RenderWindow& window) {
        // Загружаем шрифт для подписей
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Ошибка загрузки шрифта" << std::endl;
            return;
        }

        // Отрисовываем все дороги
        for (size_t i = 0; i < edges.size(); ++i) {
            const auto& edge = edges[i];
            sf::Vector2f from = nodePositions[edge.first];
            sf::Vector2f to = nodePositions[edge.second];

            // Линия дороги
            sf::Vertex line[] = {
                sf::Vertex(from, sf::Color::Black),
                sf::Vertex(to, sf::Color::Black)
            };
            window.draw(line, 2, sf::Lines);

            // Подпись с расстоянием
            sf::Text weightText(std::to_string(edgeWeights[i]), font, 16);
            weightText.setFillColor(sf::Color::Red);
            weightText.setPosition((from.x + to.x) / 2, (from.y + to.y) / 2);
            window.draw(weightText);
        }

        // Отрисовываем все города
        for (size_t i = 0; i < nodePositions.size(); ++i) {
            // Круг, представляющий город
            sf::CircleShape circle(20);
            circle.setFillColor(sf::Color::Green);
            circle.setPosition(nodePositions[i].x - 20, nodePositions[i].y - 20);
            circle.setOutlineThickness(2);
            circle.setOutlineColor(sf::Color::Black);
            window.draw(circle);

            // Подпись города (его название)
            sf::Text nodeText(cityNames[i], font, 16);
            nodeText.setFillColor(sf::Color::Black);
            nodeText.setPosition(nodePositions[i].x - 20, nodePositions[i].y + 25);
            window.draw(nodeText);
        }
    }

    // Геттеры для доступа к данным графа
    size_t getNodeCount() const { return nodePositions.size(); }
    const std::vector<std::pair<int, int>>& getEdges() const { return edges; }
    const std::vector<sf::Vector2f>& getNodePositions() const { return nodePositions; }
    const std::vector<std::string>& getCityNames() const { return cityNames; }

    // Установка позиции города
    void setNodePosition(int index, float x, float y) {
        if (index >= 0 && index < nodePositions.size()) {
            nodePositions[index] = sf::Vector2f(x, y);
        }
    }

    // Установка названия города
    void setCityName(int index, const std::string& name) {
        if (index >= 0 && index < cityNames.size()) {
            cityNames[index] = name;
        }
    }

    // Ввод данных о городах и дорогах с консоли
    void inputFromConsole() {
        int cityCount;
        std::cout << "Введите количество городов: ";
        std::cin >> cityCount;

        // Ввод информации о городах
        for (int i = 0; i < cityCount; ++i) {
            std::string name;
            float x, y;
            
            std::cout << "Город #" << i + 1 << ":\n";
            std::cout << "  Название: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            
            // Для простоты располагаем города по кругу
            x = 400 + 300 * cos(2 * 3.14159 * i / cityCount);
            y = 300 + 300 * sin(2 * 3.14159 * i / cityCount);
            
            addNode(x, y, name);
        }

        // Ввод информации о дорогах
        std::cout << "\nВведите количество дорог: ";
        int edgeCount;
        std::cin >> edgeCount;

        for (int i = 0; i < edgeCount; ++i) {
            int from, to;
            float weight;
            
            std::cout << "Дорога #" << i + 1 << ":\n";
            
            // Выводим список городов для справки
            std::cout << "  Доступные города:\n";
            for (int j = 0; j < cityCount; ++j) {
                std::cout << "    " << j << ": " << cityNames[j] << "\n";
            }
            
            std::cout << "  Индекс первого города: ";
            std::cin >> from;
            std::cout << "  Индекс второго города: ";
            std::cin >> to;
            std::cout << "  Расстояние между городами: ";
            std::cin >> weight;
            
            addEdge(from, to, weight);
        }
    }
};

// Класс для визуального интерфейса
class GraphEditor {
private:
    Graph graph;                    // Наш граф с городами
    sf::RenderWindow window;        // Окно SFML
    int selectedNode = -1;          // Выбранный город
    bool addingEdge = false;        // Режим добавления дороги
    int edgeStart = -1;             // Начальный город для добавляемой дороги

public:
    GraphEditor() : window(sf::VideoMode(800, 600), "Задача коммивояжера") {
        // Можно добавить начальные данные для демонстрации
        // или оставить граф пустым для ввода с консоли
    }

    void run() {
        // Сначала вводим данные с консоли
        graph.inputFromConsole();
        
        // Затем запускаем визуальный интерфейс
        while (window.isOpen()) {
            handleEvents();
            render();
        }
    }

private:
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
                }
            }

            // Обработка нажатий клавиш
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::T) {
                    // Решение задачи коммивояжера
                    graph.solveTSP();
                } else if (event.key.code == sf::Keyboard::A) {
                    // Переключение режима добавления дорог
                    addingEdge = !addingEdge;
                    edgeStart = -1;
                }
            }
        }
    }

    void handleLeftClick(int x, int y) {
        // Проверяем, кликнули ли на город
        const auto& positions = graph.getNodePositions();
        for (size_t i = 0; i < positions.size(); ++i) {
            float dx = positions[i].x - x;
            float dy = positions[i].y - y;
            if (dx * dx + dy * dy <= 400) { // Проверяем попадание в круг радиусом 20px
                if (addingEdge) {
                    // Режим добавления дороги
                    if (edgeStart == -1) {
                        edgeStart = i;
                    } else {
                        if (edgeStart != i) {
                            // Запрашиваем расстояние между городами
                            float weight;
                            std::cout << "Введите расстояние между " 
                                      << graph.getCityNames()[edgeStart] << " и " 
                                      << graph.getCityNames()[i] << ": ";
                            std::cin >> weight;
                            graph.addEdge(edgeStart, i, weight);
                        }
                        edgeStart = -1;
                    }
                }
                return;
            }
        }
    }

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
                "ЛКМ на городе: Выбрать город\n"
                "A: Вкл/выкл режим добавления дорог\n"
                "T: Решить задачу коммивояжера\n"
                "После выбора двух городов введите расстояние между ними"
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