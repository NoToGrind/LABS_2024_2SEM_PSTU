#include <iostream>

using namespace std;

class Pair
{
private:
	int first;
	double second;
public:
	Pair() : first(0), second(0.0) {}
	Pair(int first, double second) : first(first), second(second) {};
	Pair(const Pair& p) : first(p.first), second(p.second) {};
	~Pair() {}
	
	int get_first() const { return first; }
	int get_second() const { return second; }
	void set_first(int f) { first = f; }
	void set_second(int s) { second = s; }

	bool operator<(const Pair& pair) const;
	bool operator>(const Pair& pair) const;
	Pair operator+(const Pair& pair) const;
	Pair operator/(size_t size) const;
	Pair operator/(const Pair& pair) const;

	friend ostream& operator<<(ostream& out, const Pair& pair);
	friend istream& operator>>(istream& in, Pair& pair);
};

bool Pair::operator<(const Pair& pair) const
{
	return (static_cast<double>(first + second) < static_cast<double>(pair.first + pair.second));
}

bool Pair::operator>(const Pair& pair) const
{
	return (static_cast<double>(first + second) > static_cast<double>(pair.first + pair.second));
}

Pair Pair::operator+(const Pair& pair) const
{
	return Pair(first + pair.first, second + pair.second);
}

Pair Pair::operator/(size_t size) const
{
	return Pair(first / size, second / size);
}

Pair Pair::operator/(const Pair& pair) const
{
	return Pair(first / pair.first, second / pair.second);
}

ostream& operator<<(ostream& out, const Pair& pair)
{
	out << '(' << pair.first << " : " << pair.second << ')';
	return out;
}

istream& operator>>(istream& in, Pair& pair)
{
	cout << "Enter pair first: "; in >> pair.first;
	cout << "Enter pair second: "; in >> pair.second;
	return in;
}

typedef vector<Pair> pvec;

pvec make_pvec(int n)
{
	pvec pv;
	Pair tmp;

	for (int i = 0; i < n; ++i)
	{
		cin >> tmp;
		pv.push_back(tmp);
	}

	return pv;
}

void print_pvec(const pvec& pv)
{
	if (pv.empty())
	{
		cout << "Vector is empty !\n";
		return;
	}

	cout << "====================\n";
	for (const auto& it : pv)
	{
		cout << it << '\n';
	}
	cout << "====================\n";
}

void add_min_at_pos(pvec& pv, int pos)
{
	if (pv.empty()) return;

	Pair min_el = pv[0];

	for (const auto& it : pv)
	{
		if (it < min_el) min_el = it;
	}

	auto it = pv.begin() + pos;

	pv.insert(it, min_el);
}

void remove_below_average(pvec& pv)
{
	if (pv.empty()) return;

	Pair avg(0, .0);

	for (const auto& it : pv)
	{
		avg = avg + it;
	}

	avg = avg / pv.size();

	pv.erase(
		remove_if(pv.begin(), pv.end(), [&avg](const Pair& pair) {return pair < avg; }), 
		pv.end()
	);
}

void divide_by_max(pvec& pv)
{
	if (pv.empty()) return;

	Pair max_el = pv[0];

	for (const auto& it : pv)
	{
		if (it > max_el) max_el = it;
	}

	for_each(pv.begin(), pv.end(), [&max_el](Pair& it)
		{ it = it / max_el; });
}

typedef queue<Pair> pque;

pque make_queue(int n)
{
	pque pq;
	Pair tmp;

	for (int i = 0; i < n; ++i)
	{
		cin >> tmp;
		pq.push(tmp);
	}

	return pq;
}

void print_pvec(const pque& pq)
{
	if (pq.empty())
	{
		cout << "Queue is empty !\n";
		return;
	}

	pque tmp = pq;

	cout << "====================\n";
	while (!tmp.empty())
	{
		cout << tmp.front() << '\n';
		tmp.pop();
	}
	cout << "====================\n";
}

void add_min_at_pos(pque& pq, int pos)
{
	if (pq.empty()) return;

	Pair min_el = pq.front();
	pque tmp = pq;

	while (!tmp.empty())
	{
		if (tmp.front() < min_el) min_el = tmp.front();
		tmp.pop();
	}

	for (int i = 0; i < pos; ++i)
	{
		tmp.push(pq.front());
		pq.pop();
	}

	tmp.push(min_el);

	while (!pq.empty()) 
	{
		tmp.push(pq.front());
		pq.pop();
	}

	pq = move(tmp);
}

void remove_below_average(pque& pq)
{
	if (pq.empty()) return;

	Pair avg(0, 0.0);
	pque tmp = pq;

	while (!tmp.empty())
	{
		avg = avg + tmp.front();
		tmp.pop();
	}

	avg = avg / pq.size();

	while (!pq.empty())
	{
		if (pq.front() > avg) tmp.push(pq.front());
		pq.pop();
	}

	pq = move(tmp);
}

void divide_by_max(pque& pq)
{
	if (pq.empty()) return;

	Pair max_el = pq.front();
	pque tmp = pq;

	while (!tmp.empty())
	{
		if (tmp.front() > max_el) max_el = tmp.front();
		tmp.pop();
	}

	while (!pq.empty())
	{
		tmp.push(pq.front() / max_el);
		pq.pop();
	}

	pq = move(tmp);
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

