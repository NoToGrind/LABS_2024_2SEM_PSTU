#include <iostream>
using namespace std;

struct Node
{
	char data;
	Node* next;
	int key;
};
struct Stack
{
	Node* head = nullptr;
	int size;
	

	//добавить элемент
	void push(char Data)
	{
		Node* node = new Node;
		node->data = Data;
		node->next = head;
		head = node;
	}

	
	//удалить элемент
	void Pop()
	{
		if (head != nullptr)
		{
			Node* node = head;
			head = head->next;
			delete node;
			size--;
		}
		return;
	}
	void insert(char key, char value) {
		Node* newNode = new Node;
		newNode->data = value;
		newNode->next = nullptr;

		if (head == nullptr) {
			std::cout << "Стек пуст, добавление невозможно." << std::endl;
			delete newNode;
			return;
		}

		if (head->data == key) {
			newNode->next = head;
			head = newNode;
			return;
		}

		Node* current = head;
		while (current->next != nullptr && current->next->data != key) {
			current = current->next;
		}

		if (current->next == nullptr) {
			std::cout << "Ключ " << key << " не найден в стеке." << std::endl;
			delete newNode;
		}
		else {
			newNode->next = current->next;
			current->next = newNode;
		}
	}

	void del(char Data) {
		Node* node = head;
		Node* prev = nullptr;

		while (node != nullptr) {
			if (node->data == Data) {
				if (prev == nullptr) {
					head == node->next;
					delete node;
					return;
				}
				else {
					prev->next = node->next;
					delete node;
					return;
				}
			}
			prev = node;
			node = node->next;
		}
		cout << "Элемент не найден" << endl;
	}

	//вывод стека на экран

	void Show()
	{
		Node* temp = head;
		while (temp != 0)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}
};

int main()
{
	setlocale(LC_ALL, "rus");
	Stack Mystack;
	int n;
	char data;
	cout << "Введите кол-о элементов, которые хотите добавить в стек:" << endl;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cout << "ВВедите " << i << " элемент:" << endl;
		cin >> data;
		Mystack.push(data);
	}
	cout << "Стек:";
	Mystack.Show();
	char Data;
	char k1;
	
	cout << "Введите индекс, перед которым надо вставить ваш элемент:" << endl;
	cin >> k1;
	
	cout << "Введите значение элемента, который хотите добавить в стеке:" << endl;
	cin >> Data;
	Mystack.insert(k1,Data);
	Mystack.Show();
	cout<< "Введите элемент, который хотите удалить в стеке:" << endl;
	cin >> Data;
	Mystack.del(Data);
	Mystack.Show();
	
}