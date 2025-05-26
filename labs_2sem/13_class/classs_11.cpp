#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <queue>
#include <list>

using namespace std;

class Time
{
private:
	int minutes;
	int seconds;
public:
	Time() : minutes{ 0 }, seconds{ 0 } {};
	Time(int m, int s) : minutes{ m }, seconds{ s } { normalize(); };
	Time(const Time& other) : minutes{ other.minutes }, seconds{ other.seconds } {};

	void normalize();

	int getMinutes() const { return minutes; }
	int getSeconds() const { return seconds; }

	void setMinutes(int m) { minutes = m; }
	void setSeconds(int s) { seconds = s; }

	Time& operator=(const Time& other);
	Time operator+(const Time& other) const;
	bool operator<(const Time& other) const;
	bool operator>(const Time& other) const;
	bool operator==(const Time& other) const;
	bool operator!=(const Time& other) const;

	friend ostream& operator<<(ostream& out, const Time& t);
	friend istream& operator>>(istream& in, Time& t);
};

void Time::normalize()
{
	if (seconds >= 60)
	{
		minutes += seconds / 60;
		seconds %= 60;
	}
}

Time& Time::operator=(const Time& other)
{
	if (this == &other) return *this;
	minutes = other.minutes;
	seconds = other.seconds;
	return *this;
}

Time Time::operator+(const Time& other) const
{
	return Time(minutes + other.minutes, seconds + other.seconds);
}

bool Time::operator<(const Time& other) const
{
	return (minutes * 60 + seconds < other.minutes * 60 + other.seconds);
}

bool Time::operator>(const Time& other) const
{
	return (minutes * 60 + seconds > other.minutes * 60 + other.seconds);
}

bool Time::operator==(const Time& other) const
{
	return (minutes * 60 + seconds == other.minutes * 60 + other.seconds);
}

bool Time::operator!=(const Time& other) const
{
	return (minutes * 60 + seconds != other.minutes * 60 + other.seconds);
}

ostream& operator<<(ostream& out, const Time& t)
{
	out << '(' << t.minutes << ':' << (t.seconds < 10 ? "0" : "") << t.seconds << ')';
	return out;
}

istream& operator>>(istream& in, Time& t)
{
	char colon;
	in >> t.minutes >> colon >> t.seconds;
	t.normalize();
	return in;
}

typedef list<float> List;

List make_list(int n)
{
	List l;
	float el;

	for (int i = 0; i < n; ++i)
	{
		el = (rand() % 1000) / 100.0f - 50.0f;
		l.push_back(el);
	}

	return l;
}

void print_list(const List& l)
{
	for (auto it = l.begin(); it != l.end(); ++it)
	{
		cout << *it << ' ';
	}
	cout << endl;
}

void push_min(List& l)
{
	float min_el = *min_element(l.begin(), l.end());
	l.push_back(min_el);
}

void remove_by_value(List& l, float value)
{
	l.remove(value);
}

void add_max_plus_min(List& l)
{
	float min_el = *min_element(l.begin(), l.end());
	float max_el = *max_element(l.begin(), l.end());
	float sum = min_el + max_el;

	for (auto it = l.begin(); it != l.end(); ++it)
	{
		*it += sum;
	}
}

typedef list<Time> TimeList;

TimeList make_time_list(int n)
{
	TimeList l;

	for (int i = 0; i < n; ++i)
	{
		l.push_back(Time(rand() % 60, rand() % 60));
	}

	return l;
}

void print_time_list(const TimeList& l)
{
	for (auto it = l.begin(); it != l.end(); ++it)
	{
		cout << *it << ' ';
	}
	cout << endl;
}

void push_min(TimeList& l)
{
	if (l.empty()) return;
	Time min_el = *min_element(l.begin(), l.end());
	l.push_back(min_el);
}

void remove_by_value(TimeList& l, const Time& value)
{
	l.remove(value);
}

void add_max_plus_min(TimeList& l)
{
	Time min_el = *min_element(l.begin(), l.end());
	Time max_el = *max_element(l.begin(), l.end());
	Time sum = min_el + max_el;

	for (auto it = l.begin(); it != l.end(); ++it)
	{
		*it = *it + sum;
	}
}

template <typename T>

class Vector
{
private:
	vector<T> data;
public:
	Vector() = default;
	Vector(int n, T val = T()) : data(n, val) {}
	Vector(const Vector& other) : data(other.data) {}

	void push_back(T val) { data.push_back(val); }
	void pop_back()
	{
		if (data.empty()) return;
		data.pop_back();
	}
	void remove(const T& value)
	{
		data.erase(remove(data.begin(), data.end(), value), data.end());
	}
	size_t size() const { return data.size(); }
	bool empty() const { return data.empty(); }

	typename vector<T>::iterator begin() { return data.begin(); }
	typename vector<T>::iterator end() { return data.end(); }

	T& operator[](size_t indx) { return data[indx]; }

	void print_vector() const
	{
		for (const auto& it : data)
		{
			cout << it << ' ';
		}
		cout << endl;
	}
	void push_min()
	{
		if (data.empty()) return;
		T min_el = *min_element(data.begin(), data.end());
		data.push_back(min_el);
	}
	void remove_by_value(const T& value)
	{
		if (data.empty()) return;
		remove(value);
	}
	void add_max_plus_min()
	{
		if (data.empty()) return;
		T min_el = *min_element(data.begin(), data.end());
		T max_el = *max_element(data.begin(), data.end());
		T sum = min_el + max_el;

		for(auto& it : data)
		{
			it = it + sum;
		}
	}
};

typedef queue<Time, list<Time>> TimeQueue;

TimeQueue make_queue(int n) 
{
	TimeQueue q;
	Time t;

	for (int i = 0; i < n; ++i) 
	{
		cin >> t;
		q.push(t);
	}

	return q;
}

void print_queue(TimeQueue q)
{
	while (!q.empty())
	{
		cout << q.front() << ' ';
		q.pop();
	}
	cout << endl;
}

void push_min(TimeQueue& q)
{
	if (q.empty()) return;

	list<Time> tmp;
	Time min_el = q.front();

	while (!q.empty())
	{
		if (q.front() < min_el) { min_el = q.front(); }
		tmp.push_back(q.front());
		q.pop();
	}
	
	for (const auto& it : tmp)
	{
		q.push(it);
	}

	q.push(min_el);
}

void remove_by_value(TimeQueue& q, const Time& value)
{
	list<Time> tmp;

	while (!q.empty())
	{
		if (q.front() != value) 
		{  
			tmp.push_back(q.front());
		}
		q.pop();
	}

	for (const auto& it : tmp)
	{
		q.push(it);
	}
}

void add_max_plus_min(TimeQueue& q) 
{
	if (q.empty()) return;

	list<Time> temp;
	Time min_val = q.front();
	Time max_val = q.front();

	while (!q.empty()) 
	{
		if (q.front() < min_val) min_val = q.front();
		if (q.front() > max_val) max_val = q.front();
		temp.push_back(q.front());
		q.pop();
	}

	Time sum = min_val + max_val;

	for (auto& t : temp) 
	{
		t = t + sum;
		q.push(t);
	}
}

template <typename T>

class VectorQueue
{
private:
	queue<T, list<T>> data;
public:
	void print_vector_queue() const
	{
		queue<T, list<T>> temp = data;

		while (!temp.empty())
		{
			cout << temp.front() << " ";
			temp.pop();
		}
		cout << endl;
	}

	size_t size() const
	{
		return data.size();
	}

	bool empty() const
	{
		return data.empty();
	}

	void push(const T& value)
	{
		data.push(value);
	}

	void pop()
	{
		if (!data.empty()) data.pop();
	}

	void push_min()
	{
		if (data.empty()) return;
		list<T> temp;
		T min_val = data.front();

		while (!data.empty())
		{
			if (data.front() < min_val) min_val = data.front();
			temp.push_back(data.front());
			data.pop();
		}

		for (const auto& item : temp)
		{
			data.push(item);
		}

		data.push(min_val);
	}

	void remove_by_value(const T& value)
	{
		list<T> temp;

		while (!data.empty())
		{
			if (!(data.front() == value))
			{
				temp.push_back(data.front());
			}
			data.pop();
		}

		for (const auto& item : temp)
		{
			data.push(item);
		}
	}

	void add_max_plus_min()
	{
		if (data.empty()) return;
		list<T> temp;
		T min_val = data.front(), max_val = data.front();

		while (!data.empty())
		{
			if (data.front() < min_val) min_val = data.front();
			if (data.front() > max_val) max_val = data.front();
			temp.push_back(data.front());
			data.pop();
		}

		T sum = min_val + max_val;

		for (auto& item : temp)
		{
			item = item + sum;
			data.push(item);
		}
	}
};

int main()
{
	return 0;
}