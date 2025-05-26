#include <iostream>

using namespace std;

class Vector {
public:
	Vector(void);
	Vector(int);
public:
	~Vector(void);
	void Add(Object*);
	friend ostream& operator <<(ostream& out, const Vector&);
private:
	Object** ptr;
	int size, cur;
};

class Rect :
	public Pair
{
public:
	Rect();
public:
	~Rect();
	void Show() ;
	Rect(int, int);
	Rect(const Rect&);

	int getLen() { return len; }
	int getWidth() { return width; }

	void setLen(int);
	void setWidth(int);
	int Sq();
	int Per();

	Rect& operator =(const Rect&);

	friend istream& operator >>(istream& in, Rect& rect);
	friend ostream& operator <<(ostream& out, const Rect& rect);

protected:
	int len, width;
};

class Pair :
	public Object {
public:
	Pair(void);
public:
	virtual ~Pair(void);
	void Show();
	Pair(int, int);
	Pair(const Pair&);

	int getFirst() { return first; }
	int getSecond() { return second; }

	void setFirst(int);
	void setSecond(int);

	Pair& operator =(const Pair&);

	friend istream& operator >>(istream& in, Pair& P);
	friend ostream& operator <<(ostream& out, const Pair& P);

protected:
	int first, second;
};

class Object {
public:
	Object() {}
public:
	~Object() {}
	virtual void Show() = 0;
};

Vector::Vector(void) {
	ptr = 0;
	size = 0;
	cur = 0;
}

Vector::~Vector(void) {
	if (ptr != 0) {
		delete[] ptr;
	}
	ptr = 0;
}

Vector::Vector(int n) {
	ptr = new Object * [n];
	cur = 0;
	size = n;
}

void Vector::Add(Object* p) {
	if (cur < size) {
		ptr[cur] = p;
		cur++;
	}
}
ostream& operator <<(ostream& out, const Vector& v) {
	if (v.size == 0) {
		out << "EMPTY" << endl;
	}
	Object** p = v.ptr;
	for (int i = 0; i < v.cur; i++) {
		(*p)->Show();
		p++;
	}
	return out;
}

Rect::Rect(void) :Pair() {
	len = 0;
	width = 0;
}

Rect::~Rect(void) {}

Rect::Rect(int L, int W): Pair(L, W) {
	this->len = L;
	this->width = W;
}

Rect::Rect(const Rect& rect) {
	len = rect.len;
	width = rect.width;
}

void Rect::setLen(int L) {
	len = L;
}
void Rect::setWidth(int W) {
	width = W;;
}

Rect& Rect::operator =(const Rect& rect) {
	if (&rect == this) {
		return *this;
	}

	len = rect.len;
	width = rect.width;

	return *this;
}
int Rect::Per()
{
	return 2*(len + width);
}
int Rect::Sq()
{

	return len * width;
}


istream& operator >>(istream& in, Rect& rect) {

	cout << "\nLen: "; in >> rect.len;
	cout << "\nWidth: "; in >> rect.width;
	return in;
}

ostream& operator <<(ostream& out, const Rect& rect) {

	out << "\nLen: " << rect.len;
	out << "\nWidth: " << rect.width;
	return out;
}
void Rect::Show()
{
	cout << "\nLEN : " << len;
	cout << "\nWIDTH : " << width;
	cout << "\n";
}

Pair::Pair(void) {
	first = 0;
	second = 0;
}
Pair::~Pair(void) {}

Pair::Pair(int F, int S) {
	first = F;
	second = S;
}

Pair::Pair(const Pair& pair) {
	first = pair.first;
	second = pair.second;
}

void Pair::setFirst(int F) {
	first = F;
}
void Pair::setSecond(int S) {
	second = S;
}

Pair& Pair::operator =(const Pair& pair) {
	if (&pair == this) {
		return *this;
	}
	first = pair.first;
	second = pair.second;
	return *this;
}

istream& operator >>(istream& in, Pair& P) {
	cout << "\nFirst: "; in >> P.first;
	cout << "\nSecond: "; in >> P.second;
	return in;
}

ostream& operator <<(ostream& out, const Pair& P) {
	out << "\nFIRST: " << P.first;
	out << "\nSECOND: " << P.second;
	return out;
}
void Pair::Show()
{
	cout << "\nFIRST : " << first;
	cout << "\nSECOND : " << second;
	cout << "\n";
}

int main()
{
	Pair example;

	cin >> example;
	cout << example << endl;

	Object* p;
	p = &example;
	p->Show();

	Rect example2;

	cin >> example2;
	cout << example2 << endl;

	p = &example2;
	p->Show();

	Vector v(5);
	Pair  a;
	Rect b;

	cin >> a >> b;
	p = &a;
	v.Add(p);
	p = &b;
	v.Add(p);
	cout << v;
	cout << "Ïëîùàäü ïðÿìîóãîëüíèêà : " << endl;
	cout << example2.Sq() << endl;
	cout << "Ïåðèìåòð ïðÿìîóãîëüíèêà : " << endl;
	cout << example2.Per() << endl;
	return 0;
}