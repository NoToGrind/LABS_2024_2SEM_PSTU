#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <SFML/Graphics.hpp>

// Узел дерева
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

// Класс бинарного дерева поиска
class BST {
private:
    Node* root;

    // Вспомогательные функции
    int height(Node* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(Node* node) {
        return height(node->right) - height(node->left);
    }

    void updateHeight(Node* node) {
        int hl = height(node->left);
        int hr = height(node->right);
        node->height = (hl > hr ? hl : hr) + 1;
    }

    Node* rotateRight(Node* p) {
        Node* q = p->left;
        p->left = q->right;
        q->right = p;
        updateHeight(p);
        updateHeight(q);
        return q;
    }

    Node* rotateLeft(Node* q) {
        Node* p = q->right;
        q->right = p->left;
        p->left = q;
        updateHeight(q);
        updateHeight(p);
        return p;
    }

    Node* balance(Node* node) {
        updateHeight(node);
        if (balanceFactor(node) == 2) {
            if (balanceFactor(node->right) < 0)
                node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        if (balanceFactor(node) == -2) {
            if (balanceFactor(node->left) > 0)
                node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        return node;
    }

    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);
        if (key < node->key)
            node->left = insert(node->left, key);
        else
            node->right = insert(node->right, key);
        return balance(node);
    }

    Node* findMin(Node* node) {
        return node->left ? findMin(node->left) : node;
    }

    Node* removeMin(Node* node) {
        if (!node->left) return node->right;
        node->left = removeMin(node->left);
        return balance(node);
    }

    Node* remove(Node* node, int key) {
        if (!node) return nullptr;
        if (key < node->key)
            node->left = remove(node->left, key);
        else if (key > node->key)
            node->right = remove(node->right, key);
        else {
            Node* q = node->left;
            Node* r = node->right;
            delete node;
            if (!r) return q;
            Node* min = findMin(r);
            min->right = removeMin(r);
            min->left = q;
            return balance(min);
        }
        return balance(node);
    }

    Node* search(Node* node, int key) {
        if (!node || node->key == key) return node;
        return search(key < node->key ? node->left : node->right, key);
    }

    void preOrder(Node* node) {
        if (node) {
            std::cout << node->key << " ";
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void inOrder(Node* node) {
        if (node) {
            inOrder(node->left);
            std::cout << node->key << " ";
            inOrder(node->right);
        }
    }

    void postOrder(Node* node) {
        if (node) {
            postOrder(node->left);
            postOrder(node->right);
            std::cout << node->key << " ";
        }
    }

    void printHorizontal(Node* node, int level = 0) {
        if (node) {
            printHorizontal(node->right, level + 1);
            for (int i = 0; i < level; i++) std::cout << "   ";
            std::cout << node->key << std::endl;
            printHorizontal(node->left, level + 1);
        }
    }

    void printVertical(Node* node) {
        if (!node) return;
        std::queue<Node*> q;
        q.push(node);
        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++) {
                Node* current = q.front();
                q.pop();
                std::cout << current->key << " ";
                if (current->left) q.push(current->left);
                if (current->right) q.push(current->right);
            }
            std::cout << std::endl;
        }
    }

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    // Функции для визуализации
    void drawTree(Node* node, sf::RenderWindow& window, float x, float y, float xOffset, float yOffset, int level = 1) {
        if (!node) return;

        // Рисуем левое поддерево
        if (node->left) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x, y),
                sf::Vertex(sf::Vector2f(x - xOffset, y + yOffset))
            };
            window.draw(line, 2, sf::Lines);
            drawTree(node->left, window, x - xOffset, y + yOffset, xOffset / 1.8f, yOffset, level + 1);
        }

        // Рисуем правое поддерево
        if (node->right) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x, y)),
                sf::Vertex(sf::Vector2f(x + xOffset, y + yOffset))
            };
            window.draw(line, 2, sf::Lines);
            drawTree(node->right, window, x + xOffset, y + yOffset, xOffset / 1.8f, yOffset, level + 1);
        }

        // Рисуем узел
        sf::CircleShape circle(20);
        circle.setFillColor(sf::Color::Green);
        circle.setOutlineThickness(2);
        circle.setOutlineColor(sf::Color::White);
        circle.setOrigin(20, 20);
        circle.setPosition(x, y);
        window.draw(circle);

        // Добавляем текст с ключом
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Font not found!" << std::endl;
            return;
        }

        sf::Text text(std::to_string(node->key), font, 20);
        text.setFillColor(sf::Color::Black);
        text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2 + 5);
        text.setPosition(x, y);
        window.draw(text);
    }

public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    void insert(int key) { root = insert(root, key); }
    void remove(int key) { root = remove(root, key); }
    bool search(int key) { return search(root, key) != nullptr; }

    void preOrder() { 
        std::cout << "Прямой обход: ";
        preOrder(root); 
        std::cout << std::endl;
    }

    void inOrder() { 
        std::cout << "Симметричный обход: ";
        inOrder(root); 
        std::cout << std::endl;
    }

    void postOrder() { 
        std::cout << "Обратный обход: ";
        postOrder(root); 
        std::cout << std::endl;
    }

    void printHorizontal() { 
        std::cout << "Горизонтальная печать:" << std::endl;
        printHorizontal(root); 
    }

    void printVertical() { 
        std::cout << "Вертикальная печать:" << std::endl;
        printVertical(root); 
    }

    void balanceTree() { root = balance(root); }

    void visualize() {
        sf::RenderWindow window(sf::VideoMode(800, 600), "Binary Search Tree Visualization");
        
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color::Black);
            drawTree(root, window, 400, 50, 200, 100);
            window.display();
        }
    }
};

int main() {
    BST tree;

    // Вставляем узлы (не менее 3 уровней)
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    tree.insert(10);
    tree.insert(25);
    tree.insert(35);
    tree.insert(45);
    tree.insert(55);
    tree.insert(65);
    tree.insert(75);
    tree.insert(85);

    // Тестируем функции
    std::cout << "Дерево после вставки:" << std::endl;
    tree.printHorizontal();
    std::cout << std::endl;

    tree.preOrder();
    tree.inOrder();
    tree.postOrder();
    std::cout << std::endl;

    tree.printVertical();
    std::cout << std::endl;

    std::cout << "Поиск 40: " << (tree.search(40) ? "Найден" : "Не найден") << std::endl;
    std::cout << "Поиск 100: " << (tree.search(100) ? "Найден" : "Не найден") << std::endl;
    std::cout << std::endl;

    std::cout << "Удаляем 30 и 70:" << std::endl;
    tree.remove(30);
    tree.remove(70);
    tree.printHorizontal();
    std::cout << std::endl;

    std::cout << "Балансируем дерево:" << std::endl;
    tree.balanceTree();
    tree.printHorizontal();
    std::cout << std::endl;

    // Визуализация дерева
    tree.visualize();

    return 0;
}