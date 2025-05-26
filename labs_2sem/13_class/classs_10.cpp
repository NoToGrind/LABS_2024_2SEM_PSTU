#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Money
{
private:
	long rubles;
	int kopecks;
	void normalize();
public:
	Money();
	Money(long rubles, int kopecks);
	Money(const Money&);
	Money& operator=(const Money&);
	~Money() = default;

	friend ostream& operator<<(ostream& out, const Money&);
	friend istream& operator>>(istream& in, Money&);
	friend fstream& operator<<(fstream& fout, const Money&);
	friend fstream& operator>>(fstream& fin, Money&);

	Money operator+(const Money&) const;
	Money operator-(const Money&) const;
	bool operator==(const Money&) const;

	void increase();
	void setRub(long rub);
	void setKop(int kop);
	long getRub() const;
	int getKop() const;
};

int make_file(const char* filename);
int print_file(const char* filename);
int delete_by_value(const char* filename, const Money& value);
int increase_by_value(const char* filename, const Money& value);
int add_file(const char* filename, int k, int n);

Money::Money() : rubles{ 0 }, kopecks{ 0 } {};
Money::Money(long rub, int kop) : rubles{ rub }, kopecks{ kop } { normalize(); }
Money::Money(const Money& m) : rubles{ m.rubles }, kopecks{ m.kopecks } {};
Money& Money::operator=(const Money& m)
{
	if (this == &m) { return *this; }
	rubles = m.rubles;
	kopecks = m.kopecks;
	return *this;
}

ostream& operator<<(ostream& out, const Money& m)
{
	out << m.rubles << ',' << (m.kopecks < 10 ? "0" : "") << m.kopecks;
	return out;
}
istream& operator>>(istream& in, Money& m)
{
	char comma;
	in >> m.rubles >> comma >> m.kopecks;
	m.normalize();
	return in;
}
fstream& operator<<(fstream& fout, const Money& m)
{
	fout << m.rubles << ',' << (m.kopecks < 10 ? "0" : "") << m.kopecks << '\n';
	return fout;
}
fstream& operator>>(fstream& fin, Money& m)
{
	char comma;
	fin >> m.rubles >> comma >> m.kopecks;
	m.normalize();
	return fin;
}

Money Money::operator+(const Money& m) const
{
	long totalRub = rubles + m.rubles;
	int totalKop = kopecks + m.kopecks;
	return Money(totalRub, totalKop);
}
Money Money::operator-(const Money& m) const
{
	return Money(rubles - m.rubles, kopecks - m.kopecks);
}
bool Money::operator==(const Money& m) const
{
	return ((rubles == m.rubles) && (kopecks == m.kopecks));
}

void Money::normalize()
{
	if (kopecks >= 100)
	{
		rubles += kopecks / 100;
		kopecks = kopecks % 100;
	}
}
void Money::increase()
{
	++rubles;
	kopecks += 50;
	normalize();
}
void Money::setRub(long rub) { rubles = rub; }
void Money::setKop(int kop) { kopecks = kop; }
long Money::getRub() const { return rubles; }
int Money::getKop() const { return kopecks; }

int make_file(const char* filename)
{
	fstream file(filename, ios::out | ios::trunc);
	if (!file) return -1;

	int c;
	cout << "Enter the number of records in the file: ";
	cin >> c;

	Money money;
	for (int i = 0; i < c; ++i)
	{
		cout << "Enter rubles and kopecks: ";
		cin >> money;
		file << money;
	}

	file.close();
	return c;
}

int print_file(const char* filename)
{
	fstream file(filename, ios::in);
	if (!file) return -1;

	int c = 0;
	Money money;
	while (file >> money)
	{
		cout << money << endl;
		++c;
	}

	file.close();
	return c;
}

int delete_by_value(const char* filename, const Money& value)
{
	ifstream in(filename);
	if (!in) return -1;

	vector<Money> v;
	Money money;
	int c = 0;

	while (in >> money)
	{
		if (money == value)
		{
			++c;
			continue;
		}
		v.push_back(money);
	}

	in.close();

	ofstream out(filename);
	if (!out) return -1;

	for (const auto& it : v)
	{
		out << it << '\n';
	}

	out.close();
	return c;
}

int increase_by_value(const char* filename, const Money& value)
{
	ifstream in(filename);
	if (!in) return -1;

	vector<Money> v;
	Money money;
	int c = 0;

	while (in >> money)
	{
		if (money == value)
		{
			++c;
			money.increase();
		}
		v.push_back(money);
	}

	in.close();

	ofstream out(filename);
	if (!out) return -1;

	for (const auto& it : v)
	{
		out << it << '\n';
	}

	out.close();
	return c;
}

int add_file(const char* filename, int k, int n)
{
	ifstream in(filename);
	if (!in) return -1;

	vector<Money> v;
	Money money;
	int it = 0;

	while (in >> money)
	{
		if (it == n)
		{
			v.push_back(money);

			for (int i = 0; i < k; ++i)
			{
				v.push_back(Money());
			}
		}
		else
		{
			v.push_back(money);
		}

		++it;
	}

	in.close();

	ofstream out(filename);
	if (!out) return -1;

	for (const auto& it : v)
	{
		out << it << '\n';
	}

	out.close();
	return k;
}

int main()
{
	make_file("test.txt");
	print_file("test.txt");
	int n = add_file("test.txt", 3, 1);
	print_file("test.txt");
	cout << n;

	return 0;
}