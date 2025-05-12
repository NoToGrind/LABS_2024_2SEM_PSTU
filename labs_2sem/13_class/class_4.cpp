#include <iostream>
#include <string>
using namespace std;

class Pair
{
public:
	Pair(void);
	virtual ~Pair(void);
	Pair(int,int);
	Pair(const Pair&);

	int getFirst(){return first;}
	int getSecond() {return second;}
	void setFirst(int);
	void setSecond(int);

	Pair& operator =(const Pair&);
	friend istream& operator >> (istream& in, Pair& P);
	friend ostream& operator << (ostream& out, const Pair& P);
	

protected:
	int first;
	int second;
};

class Rectangle
{
public:
	Rectangle(void);
	~Rectangle(void);
	Rectangle(int, int);
	Rectangle(const Rectangle&);

	int getLength() {return length;}
	int getWidth(){return width;}
	void setLength(int);
	void setWidth(int);
	int Square();
	int Perimetr();

	Rectangle& operator =(const Rectangle&);
	friend istream& operator >>(istream& in, Rectangle& rect);
	friend ostream& operator <<(ostream& out, const Rectangle& rect);
protected:
	int length;
	int width;
};

Pair::Pair(void)
{
	first = 0;
	second = 0;
}

Pair::~Pair(void){}

Pair::Pair(int F, int S)
{
	first = F;
	second = S;
}

Pair::Pair(const Pair& pair)
{
	first = pair.first;
	second = pair.second;
}

void Pair::setFirst(int F){first = F;}
void Pair::setSecond(int S){second = S;}

Pair& Pair::operator =(const Pair& pair)
{
	if(&pair == this){return *this;}
	first = pair.first;
	second = pair.second;
	return *this;
}

istream& operator >>(istream& in, Pair& P)
{
	cout << "\nFirst: "; in >> P.first;
	cout << "\nSecond: "; in >> P.second;
	return in;
}

ostream& operator <<(ostream& out, const Pair& P) {
	out << "\nFirst: "; out << P.first;
	out << "\nSecond: "; out << P.second;
	return out;
}

Rectangle::Rectangle(void)
{
	length = 0;
	width = 0;
}
Rectangle::~Rectangle(void){}

Rectangle::Rectangle(int L, int W)
{
	length = L;
	width = W;
}

Rectangle::Rectangle(const Rectangle& rectangle)
{
	length = rectangle.length;
	width = rectangle.width;
}

void Rectangle::setLength(int L){length = L;}
void Rectangle::setWidth(int W){width = W;}

Rectangle& Rectangle::operator=(const Rectangle& rectangle)
{
	if (&rectangle==this){return *this;}
	length = rectangle.length;
	width = rectangle.width;
	return *this;
}

int Rectangle::Perimetr(){return (length+width)*2;}
int Rectangle::Square(){return length*width;}

istream& operator >> (istream& in, Rectangle& rectangle)
{
	cout << "\nLength: "; in >> rectangle.length;
	cout << "\nWidth: "; in >> rectangle.width;
	return in;
}

ostream& operator << (ostream& out, const Rectangle& rectangle)
{
	cout << "\nLength: "; out << rectangle.length;
	cout << "\nWidth: "; out << rectangle.width;
	return out;
}

int main() 
{
	Pair numZero;
	cin >> numZero;
	cout << numZero;
	Pair numOne(12, 13);
	cout << numOne;
	numZero = numOne;
	cout << numZero;

	Rectangle rectangle;
	cin >> rectangle;
	cout << rectangle << endl;
	cout << "P = " << endl;
	cout << rectangle.Perimetr() << endl;
	cout << "S = " << endl;
	cout << rectangle.Square() << endl;
	
	return 0;
}