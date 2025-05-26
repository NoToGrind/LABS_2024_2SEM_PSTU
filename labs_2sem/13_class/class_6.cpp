#include <ostream>
#include <iostream>
using namespace std;
class Iterator
{
	friend class Vector;
public:
	Iterator() { elem = 0; }
	Iterator(const Iterator& it) {elem = it.elem; }
	bool operator==(const Iterator& it) { return elem == it.elem; }
	bool operator!=(const Iterator& it) { return elem != it.elem; };
	void operator++() { ++elem; };
	void operator--() { --elem; }
	Iterator operator+(int n) const
	{
		Iterator tmp(*this);
		tmp.elem += n;
		return tmp;
	}
	int& operator *() const { return*elem; }
private:
	int* elem;
};
class Vector
{
public:
	Vector(int s, int k = 0);
	Vector(const Vector& a);
	~Vector();
	Vector& operator=(const Vector& a);
	int& operator[](int index);
	Vector operator+(const Vector& a);
	int operator()();
	friend std::ostream& operator<<(std::ostream& out, const Vector& a);
	friend std::istream& operator>>(std::istream& in, Vector& a);
	Iterator first() { return beg; }
	Iterator last() { return end; }
private:
	int size;
	int* data;
	Iterator beg;
	Iterator end;
};

Vector::Vector(int s, int k)
{
	size = s;
	data = new int[size];
	for (int i = 0; i < size; i++)
		data[i] = k;
	beg.elem = &data[0];
	end.elem = &data[size];
}
Vector::Vector(const Vector& a) {
	size = a.size;
	data = new int[size];
	for (int i = 0; i < size; i++) {
		data[i] = a.data[i];
	}
	beg = a.beg;
	end = a.end;
}

Vector::~Vector() {
	delete[]data;
	data = 0;
}

Vector&Vector::operator =(const Vector& a) {
	if (this == &a) return *this;

	size = a.size; // Äîáàâëÿåì îáíîâëåíèå ðàçìåðà
	delete[] data;
	data = new int[size];
	for (int i = 0; i < size; i++) {
		data[i] = a.data[i];
	}
	beg = a.beg;
	end = a.end;
	return *this;
}


int& Vector::operator[](int index) {
	if (index < size) {
		return data[index];
	}
	else {
		cout << "\nError (index > size)\n";
	}
}

Vector Vector::operator+(const Vector&a) {
	Vector temp(size);
	for (int i = 0; i < size; i++) {
		temp.data[i] = data[i] + a.data[i];
	}
	return temp;
}

int Vector::operator() () {
	return size;
}

ostream& operator << (ostream& out, const Vector&a) {
	for (int i = 0; i < a.size; ++i) {
		cout << "OUT: " << i << " = ";
		out << a.data[i] << " ";
	}
	return out;
}

istream& operator >> (istream& in, Vector& a) {
	for (int i = 0; i < a.size; i++) {
		cout << "IN: " << i << " = ";
		in >> a.data[i];
	}
	return in;
}

int main()
{
	Vector a(5);
	Vector b(5);
	cin >> a;
	cin>> b;
	Vector sum = a + b;
	cout << "\nSum: " << sum << endl;

	cout << "First element: " << *a.first() << endl;

	Iterator i = a.first();
	i=i+1;
	cout << "Second element: " << *i << endl;
	for (i = a.first(); i != a.last();++i)cout << *i <<" ";
	cout << endl;
	return 0;
}
