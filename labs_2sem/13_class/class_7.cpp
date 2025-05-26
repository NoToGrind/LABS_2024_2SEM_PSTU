#include <iostream>

using namespace std;

template <class T>
class Vector
{
private:
	int size;
	T* data;
public:
	Vector(int s, T k);
	Vector(const Vector<T>& obj);
	~Vector();
	Vector& operator=(const Vector<T>& obj);
	T& operator[](int index);
	Vector operator*(const Vector<T>& obj);
	int operator()();
	friend ostream& operator<<(ostream& out, const Vector<T>& obj)
	{
		for (int i = 0; i < obj.size; ++i)
		{
			out << obj.data[i] << ' ';
		}

		return out;
	}
	friend istream& operator>>(istream& in, Vector<T>& obj)
	{
		for (int i = 0; i < obj.size; ++i)
		{
			in >> obj.data[i];
		}

		return in;
	}
};

class Time
{
private:
	int sec;
	int min;
public:
	Time();
	Time(int s, int m);
	Time(const Time& obj);
	Time& operator=(const Time& obj);
	Time operator*(const Time& obj);
	friend ostream& operator<<(ostream& out, const Time& obj);
	friend istream& operator>>(istream& in, Time & obj);
};

template <class T>
Vector<T>::Vector(int s, T k)
{
	size = s;
	data = new T[size];
	for (int i = 0; i < size; ++i)
	{
		data[i] = k;
	}
}

template <class T>
Vector<T>::Vector(const Vector<T>& obj)
{
	size = obj.size;
	data = new T[size];
	for (int i = 0; i < size; ++i)
	{
		data[i] = obj.data[i];
	}
}

template <class T>
Vector<T>::~Vector()
{
	delete[] data;
	data = nullptr;
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& obj)
{
	if (this == &obj)
	{
		return *this;
	}

	size = obj.size;
	delete[] data;
	data = new T[size];

	for (int i = 0; i < size; ++i)
	{
		data[i] = obj.data[i];
	}

	return *this;
}

template <class T>
T& Vector<T>::operator[](int index)
{
	if (index < size)
	{
		return data[index];
	}
	else
	{
		cerr << "Index out of range !" << endl;
		exit(1);
	}
}

template <class T>
Vector<T> Vector<T>::operator*(const Vector<T>& obj)
{
	if (size != obj.size)
	{
		cerr << "Vectors have different sizes !" << endl;
		exit(1);
	}

	Vector<T> tmp(size, 0);

	for (int i = 0; i < size; ++i)
	{
		tmp.data[i] = data[i] * obj.data[i];
	}
	return tmp;
}

template <class T>
int Vector<T>::operator()()
{
	return size;
}

Time::Time() : sec{ 0 }, min{ 0 } {}
Time::Time(int s, int m) : sec{ s }, min{ m } {}
Time::Time(const Time& obj) : sec{ obj.sec }, min{ obj.min } {}
Time& Time::operator=(const Time& obj)
{
	if (this == &obj)
	{
		return *this;
	}
	
	sec = obj.sec;
	min = obj.min;

	return *this;
}
Time Time::operator*(const Time& obj)
{
	int total_sec = (min * 60 + sec) * (obj.min * 60 + obj.sec);
	return Time(total_sec % 60, total_sec / 60);
}
ostream& operator<<(ostream& out, const Time& obj)
{
	out << obj.min << ':' << obj.sec;
	return out;
}
istream& operator>>(istream& in, Time& obj)
{
	cout << "Enter minutes: ";
	in >> obj.min;
	cout << "Enter seconds: ";
	in >> obj.sec;
	return in;
}

using namespace std;

int main()
{
	Time t;
	cin >> t;
	cout << t << endl;
	Vector<Time>A(5, t);
	cin >> A;
	cout << A << endl;
	Vector <Time>B(10, t);
	cout << B << endl;
	B = A;
	cout << B << endl;
	cout << A[2] << endl;
	cout << "size=" << A() << endl;

	return 0;
}