#include <iostream>
#include <string>
using namespace std;

class Time
{
	int min, sec;
public:
	Time(){min=0,sec=0;};
	Time(int m,int s){min=m;sec=s;}
	Time(const Time&t){min=t.min;sec=t.sec;}
	~Time(){};
	int get_min() { return min; };
	int get_sec() { return sec; };
	void set_min(int m) { min = m; }
	void set_sec(int s) { sec = s; }
	Time& operator =(const Time&);
	Time& operator ++();
	Time operator ++(int);
	Time operator +(const Time&);
	friend istream& operator >>(istream& in, Time& temp);
	friend ostream& operator <<(ostream& out, const Time& temp);
};

Time& Time::operator =(const Time& temp) {
	if (&temp == this) {return *this;}
	min = temp.min;
	sec = temp.sec;
	return *this;
}

Time& Time::operator ++() {
	int temp =min * 60 + sec;
	temp++;
	min = temp / 60;
	sec = temp % 60;
	return *this;
}

Time Time::operator ++(int) {
	int temp = min * 60 + sec;
	temp++;
	Time t1(min, sec);
	min = temp / 60;
	sec = temp % 60;
	return t1;
}

Time Time::operator +(const Time& temp) {
	int t1 = min*60+sec;
	int t2 = temp.min * 60 + temp.sec;
	Time temp2;
	temp2.min = (t1 + t2) / 60;
	temp2.sec = (t1 + t2) % 60;
	return temp2;
}

istream& operator >>(istream& in, Time& temp) {
	cout << "min: ";
	in >> temp.min;
	cout << "sec: ";
	in >> temp.sec;
	return in;
}

ostream& operator <<(ostream& out, const Time& temp) {
	return (out << temp.min << " : " << temp.sec);
}

int main() {
	Time a, b, c;
	cin >> a >> b;
	++a;

	cout << a << endl;
	c = (a++) + b;

	cout << "A = " << a << endl;
	cout << "B = " << b << endl;
	cout << "C = " << c << endl;
	return 0;
}