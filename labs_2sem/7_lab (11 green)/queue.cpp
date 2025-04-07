#include <iostream>
using namespace std;

struct Node {
	char data;
	Node* next;
};

struct Queue
{
	int size;
	Node* head;
	Node* tail;

	void initQ(Queue& q, char value)
	{
		Node* newNode = new Node;
		newNode->data = value;
		newNode->next = nullptr;
		q.head = newNode;
		q.tail = newNode;
		q.size = 1;
		return;
	}
	void push(Queue& q, char data)
	{
		Node* newNode = new Node{ data, nullptr };
		q.tail->next = newNode;
		q.tail = newNode;
		q.size++;
		return;
	}
	void pop(Queue& q)
	{
		if (q.head != nullptr)
		{
			Node* temp = q.head;
			q.head = q.head->next;
			delete temp;
			q.size--;
		}
		return;
	}
	void remove(Queue& q, char key)
	{
		int size = q.size;
		for (int i = 1; i <= size; i++)
		{
			if (q.head->data == key)
			{
				pop(q);
			}
			else
			{
				push(q, q.head->data);
				pop(q);
			}
		}
		return;
	}
	void insert(Queue& q, int k, int m)
	{
		for (int i = 1; i < m; i++)
		{
			push(q, q.head->data);
			pop(q);
		}
		char value;
		for (int i = 1; i <= k; i++)
		{
			cout << "ВВедите элемент для вставки:";
			cin >> value;
			push(q, value);
		}
		int size = q.size;
		for (int i = m; i <= size - k; i++)
		{
			push(q, q.head->data);
			pop(q);
		}
		return;
	}
	void create_queue(Queue& q, int n)
	{
		char value;
		cout << "Введите элемент №1: ";
		cin >> value;
		initQ(q, value);
		for (int i = 2; i <= n; i++)
		{
			cout<< "Введите элемент № "<<i<<":";
			cin >> value;
			push(q, value);
		}
		return;
	}
	void delete_el(Queue& q)
	{
		while (q.head->next != nullptr)
		{
			pop(q);
		}
		Node* temp = q.head;
		q.head = nullptr;
		q.size--;
		delete temp;
		return;
	}
	void print(Queue& q)
	{
		cout << "Начало" << endl;
		Node* temp = q.head;
		while (temp != nullptr)
		{
			cout << temp->data << "->";
			temp = temp->next;
		}
		cout << "Конец" << endl;
		return;
	}
};

int main()
{
	setlocale(LC_ALL, "rus");
	Queue q;
	int n; 
	cout << "Введите количество в очереди:";
	cin >> n; 
	q.create_queue(q, n);
	cout << endl;
	q.print(q);
	int k;
	int m;
	cout << "Ведите индекс элемента, перед которым будет добавлен ваш элемент:";
	cin >> m;
	cout << "ВВедите количеcтво элементов, которые хотите добавить: " << endl;
	cin >> k;
	q.insert(q, k, m);
	q.print(q);
	cout << "ВВедите элемент, который хотите удалить: " << endl;
	char key;
	cin >> key;
	q.remove(q, key);
	q.print(q);
}