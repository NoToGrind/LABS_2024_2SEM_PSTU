#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

struct Node
{
    char data;
    Node* next;
    Node* prev;
};

struct List {
    Node* head = nullptr;
    Node* tail = nullptr;

    void push_front (char Data) {
        Node* node = new Node;
        node->data = Data;
        node->next = head;
        node->prev = nullptr;

        if (head != nullptr) {
            head->prev = node;
        }
        head = node;
        if (tail == nullptr) {
            tail = node;
        }
    }
    void push_back(char Data)
    {
        Node* node = new Node;
        node->next = NULL;
        node->data=Data;
        if (head != NULL) {
            node->prev = tail;
            tail->next = node;
            tail = node;
        }
        else {
            node->prev = NULL;
            head = tail = node;
        }
    }

    void print() {
        Node* node = head;
        while (node) {
            cout << node->data << " ";
            node = node->next;
        }
        cout << endl;
    }
    Node* getAt(int k)
    {
        Node* node = head;
        int n = 0;

        while (n != k)
        {
            if (node == nullptr)
                return node;
            node = node->next;
            n++;
        }
        return node;
    }
    Node* operator[](int k)
    {
        return getAt(k);
    }
    int size()
    {
        int count = 0;
        Node* current = head;
        while (current != nullptr)
        {
            count++;
            current = current->next;
        }
        return count;
    }
    void insert(int index, char Data)
    {
        if (index == 0)
        {
            push_front(Data);
        }
        else if (index == size())
        {
            push_back(Data);
        }
        else
        {
            Node* newNode = new Node();
            newNode->data = Data;

            Node* current = head;
            for (int i = 0; i < index - 1; i++)
            {
                current = current->next;
            }

            newNode->next = current->next;
            newNode->prev = current;
            current->next->prev = newNode;
            current->next = newNode;
        }
    }


    //удаление в конце списка
    void pop_back() {
        if (tail == NULL) return;

        Node* ptr = tail->prev;
        if (ptr != NULL)
            ptr->next = NULL;
        else
            head = NULL;

        delete tail;
        tail = ptr;
    }
    //удаление в начале списка
    void pop_front() {
        if (head == NULL) return;

        Node* ptr = head->next;
        if (ptr != NULL)
            ptr->prev = NULL;
        else
            tail = NULL;

        delete head;
        head = ptr;
    }
    //удаление с заданным элементом
    void erase(int index) {
        Node* ptr = getAt(index);
        if (ptr == NULL)
            return;

        if (ptr->prev == NULL) {
            pop_front();
            return;
        }

        if (ptr->next == NULL) {
            pop_back();
            return;
        }

        Node* left = ptr->prev;
        Node* right = ptr->next;
        left->next = right;
        right->prev = left;

        delete ptr;
    }
};
void main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");
    List list;
    int count;
    char Data, data;

    cout << "Ведите количество элментов в списке: ";
    cin >> count;

    if (count >= 0) {
        for (int i = 0; i < count; i++) {
            cout << "Введите " << i + 1 << " элемент: ";
            cin >> Data;
            list.push_back(Data);
        }
        list.print();
    }
    int k;
    cout << "Введите индекс добавляемого элемента:" << endl;
    cin >> k;
    cout << "Ведите значение добавляемого элемента:" << endl;
    cin >> data;
    list.insert(k, data);
    list.print();
    int k1;
    cout << "Введите индекс удаляемого элемента:" << endl;
    cin >> k1;
    list.erase(k1);
    list.print();
}