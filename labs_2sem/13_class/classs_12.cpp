#include <iostream>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

class Pair 
{
private:
    int first;
    int second;
public:
    Pair() { first = 0; second = 0; }
    Pair(int f, int s) { first = f; second = s; }
    Pair(const Pair& p) { first = p.first; second = p.second; }

    int get_first() const { return first; }
    int get_second() const { return second; }
    void set_first(int f) { first = f; }
    void set_second(int s) { second = s; }

    Pair operator+(const Pair&);
    Pair operator-(const Pair&);
    Pair operator/(const Pair&);
    Pair operator/(const int);
    bool operator<(const Pair&) const;
    bool operator>(const Pair&) const;
    friend istream& operator>>(istream& in, Pair& p);
    friend ostream& operator<<(ostream& out, const Pair& p);
};

template<class T>

class Container 
{
private:
    list<T> lst;
public:
    Container() {}
    Container(int n) 
    {
        T a;
        for (int i = 0; i < n; i++) 
        {
            cin >> a;
            lst.push_back(a);
        }
    }

    void Print() 
    {
        for (auto it = lst.begin(); it != lst.end(); ++it) 
        {
            cout << *it << " ";
        }
        cout << endl;
    }

    T find_min() 
    {
        return *min_element(lst.begin(), lst.end());
    }

    void add_at_position(int pos, T val) 
    {
        auto it = lst.begin();
        advance(it, pos);
        lst.insert(it, val);
    }

    void remove_below_average() 
    {
        T sum = accumulate(lst.begin(), lst.end(), T());
        T avg = sum / lst.size();

        for (auto it = lst.begin(); it != lst.end(); ) 
        {
            if (*it < avg) it = lst.erase(it);
            else ++it;
        }
    }

    void divide_by_max() 
    {
        T max_val = *max_element(lst.begin(), lst.end());
        for (auto& elem : lst) 
        {
            elem = elem / max_val;
        }
    }
};

Pair Pair::operator+(const Pair& p) 
{
    int f = first + p.first;
    int s = second + p.second;
    f += s / 100;
    s = s % 100;
    return Pair(f, s);
}

Pair Pair::operator-(const Pair& p) 
{
    int f = first - p.first;
    int s = second - p.second;
    return Pair(f, s);
}

Pair Pair::operator/(const Pair& p) 
{
    int total1 = first * 100 + second;
    int total2 = p.first * 100 + p.second;
    return Pair(0, total1 / total2);
}

Pair Pair::operator/(const int n) 
{
    int total = first * 100 + second;
    total /= n;
    return Pair(total / 100, total % 100);
}

bool Pair::operator<(const Pair& p) const
{
    int total1 = first * 100 + second;
    int total2 = p.first * 100 + p.second;
    return total1 < total2;
}

bool Pair::operator>(const Pair& p) const
{
    int total1 = first * 100 + second;
    int total2 = p.first * 100 + p.second;
    return total1 > total2;
}

istream& operator>>(istream& in, Pair& p) 
{
    cout << "First: "; in >> p.first;
    cout << "Second: "; in >> p.second;
    return in;
}

ostream& operator<<(ostream& out, const Pair& p) 
{
    out << '(' << p.first << "," << p.second << ')';
    return out;
}

typedef multimap<int, float> FloatMultimap;

FloatMultimap make_float_multimap(int n)
{
	FloatMultimap fm;
	float el;

	for (int i = 0; i < n; ++i)
	{
		cout << "Enter multimap element: ";
		cin >> el;
		fm.insert(make_pair(i, el));
	}

	return fm;
}

void print_float_multimap(const FloatMultimap& fm)
{
	cout << "==============================\n";
	for (auto it = fm.begin(); it!=fm.end(); ++it)
	{
		cout << '(' << it->first << ':' << it->second << ")\n";
	}
	cout << "==============================\n";
}

void add_min_at_position(FloatMultimap& fm, const int pos)
{
	if (pos < 0 || pos > fm.size() || fm.empty()) return;

	float min_el = (fm.begin())->second;

	for (const auto& it : fm)
	{
		if (it.second < min_el) min_el = it.second;
	}

	auto it = fm.begin();
	advance(it, pos);

	fm.insert(it, make_pair(pos, min_el));
}

void remove_below_average(FloatMultimap& fm)
{
	float sum = 0;
	for (const auto& it : fm) sum+=it.second;

	float avg = sum / fm.size();

	for (auto it = fm.begin(); it != fm.end(); )
	{
		if (it->second < avg) it = fm.erase(it);
		else ++it;
	}
}

void divide_by_max(FloatMultimap& fm)
{
	if (fm.empty()) return;
	float max_el = (fm.begin())->second;

	for (const auto& it : fm)
	{
		if (it.second > max_el) max_el = it.second;
	}

	for (auto& it : fm) it.second /= max_el;
}

typedef multimap<int, Pair> PairMultimap;

PairMultimap make_pair_multimap(int n)
{
	PairMultimap pm;
	Pair el;

	for (int i = 0; i < n; ++i)
	{
		cout << "Enter pair: " << endl;
		cin >> el;
		pm.insert(make_pair(i, el));
	}

	return pm;
}

void print_pair_multimap(const PairMultimap& pm)
{
	cout << "==============================\n";
	for (auto it = pm.begin(); it != pm.end(); ++it)
	{
		cout << '(' << it->first << ':' << it->second << ")\n";
	}
	cout << "==============================\n";
}

void add_min_at_position(PairMultimap& pm, const int pos)
{
	if (pos < 0 || pos > pm.size() || pm.empty()) return;

	Pair min_el = (pm.begin())->second;

	for (const auto& it : pm)
	{
		if (it.second < min_el) min_el = it.second;
	}

	auto it = pm.begin();
	advance(it, pos);

	pm.insert(it, make_pair(pos, min_el));
}

void remove_below_average(PairMultimap& pm)
{
	if (pm.empty()) return;

	Pair sum_pair;

	for (const auto& it : pm)
	{
		sum_pair.set_first(sum_pair.get_first() + it.second.get_first());
		sum_pair.set_second(sum_pair.get_second() + it.second.get_second());
	}

	sum_pair.set_first(sum_pair.get_first() / pm.size());
	sum_pair.set_second(sum_pair.get_second() / pm.size());

	for (auto it = pm.begin(); it != pm.end(); )
	{
		if ((it->second) < sum_pair) it = pm.erase(it);
		else ++it;
	}
}

void divide_by_max(PairMultimap& pm)
{
	if (pm.empty()) return;
	
	Pair max_pair = pm.begin()->second;

	for (const auto& it : pm)
	{
		if (it.second > max_pair) max_pair = it.second;
	}

	for (auto& it : pm)
	{
		it.second = it.second / max_pair;
	}
}

int main()
{
	return 0;
}

