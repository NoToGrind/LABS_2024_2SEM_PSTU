#include <iostream>
using namespace std;
struct Node
{
    char data;
    Node* next_ptr;

    void adddata(char Data)
    {
        data = Data;
        next_ptr = nullptr;
    }
};
struct List
{
    Node* head = nullptr;
    Node* tail = nullptr;

    //добавление элемента в конец списка
    void push(char data)
    {
        Node* node = new Node;
        node->adddata(data);
        if (head == nullptr) head = node;
        if (tail != nullptr) tail->next_ptr = node;
        tail = node;
    }

    //добавление в начало списка
    void push1(char data)
    {
        Node* node = new Node;
        node->adddata(data);
        node->next_ptr = head;
        head = node;
        if (tail == nullptr) tail = node;
    }



    //добавление после элемента с заданным индексом
    void insert(int k, char data)
    {
        if (k < 0) return;
        if (k == 0)
        {
            Node* node = new Node;
            node->adddata(data);
            node->next_ptr = head;
            head = node;
            return;
        }
        Node* node = new Node;
        node->adddata(data);
        Node* current = head;
        for (int i = 0; i < k - 1; i++)
        {
            current = current->next_ptr;
        }
        node->next_ptr = current->next_ptr;
        current->next_ptr = node;   
    }

    //удаление первого элемента
    void del_elem()
    {
        if (head == nullptr) return;
        if (head == tail)
        {
            delete tail;
            head = tail = nullptr;
            return;
        }
        Node* node = head;
        head = node->next_ptr;
        delete node;
    }

    //удаление последнего элемента
    void last_elem()
    {
        if (tail == nullptr) return;
        if (head == tail)
        {
            delete tail;
            head = tail = nullptr;
            return;
        }
        Node* node = head;
        for (; node->next_ptr != tail; node = node->next_ptr);
        node->next_ptr = nullptr;
        delete tail;
        tail = node;
    }
    //возращение элемента по индексу
    Node* get(int k)
    {
        if (k < 0) return 0;
        Node* node = head;
        int n =0;
        while (node && n != k && node->next_ptr)
        {
            node = node->next_ptr;
            n++;
        }
        if (n == k) return node;
        else return nullptr;
    }
    //удаление элемента с заданным индексом
    void erase(int k, char data)
    {
        if (k < 0) return;
        if (k == 0)
        {
            push1(data);
            return;
        }
        Node* left = get(k - 1);
        Node* node = left->next_ptr;
        if (node == nullptr) return;
        Node* right = node->next_ptr;
        left->next_ptr = right;
        if (node == tail)
        {
            tail = left;
        }
        delete node;
    }
};
int main()
{
    setlocale(LC_ALL, "rus");
    List list;
    char temp;
    int n;
    cout << "Введите количество элементов в списке: " << endl;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << "Введите " << i + 1 << " элемент" << endl;
        cin >> temp;
        list.push(temp);
    }
    cout << endl;
    for (Node* node = list.head; node != list.tail->next_ptr; node = node->next_ptr)
    {
        cout << node->data << ' ';
    }
    cout << endl << endl;
    
    cout << "Введите индекс добавляемого элемента:" << endl;
    int k;
    cin >> k;
    char Data;
    cout << "Введите значение добавляемого элемента:" << endl;
    cin >> Data;
    list.insert(k,Data);
    cout << "Новый список:" << endl;
    for (Node* node = list.head; node != list.tail->next_ptr; node = node->next_ptr)
    {
        cout << node->data << ' ';
    }
    cout << endl << endl;
    int k1;
    cout << "Введите индекс удаляемого элемента:" << endl;
    cin >> k1;
    cin >> Data;
    list.erase(k1, Data);
    cout << "Новый список:" << endl;
    for (Node* node = list.head; node != list.tail->next_ptr; node = node->next_ptr)
    {
        cout << node->data << ' ';
    }
    cout << endl << endl;
}