#include <iostream>
#include <string>
using namespace std;

class Book
{
	string name;
	string author;
	int year;

public:
	Book();
	Book(string,string,int);
	Book(const Book&);
	~Book();
	string get_name();
	void set_name(string);
	string get_author();
	void set_author(string);
	int get_year();
	void set_year(int);
	void show();
};

Book::Book()
{
	name="";
	author="";
	year=0;
	cout << "no parametri for object"<<this<<endl;
}

Book::Book(string N, string K, int S)
{
	name=N;
	author=K;
	year=S;
	cout << "s parametrami for object"<<this<<endl;
}

Book::Book(const Book &t)
{
	name=t.name;
	author = t.author;
	year = t.year;
	cout << "ctrl c for object"<<this<<endl;
}
//selectori
Book::~Book()
{
	cout << "destructor for object"<<this<<endl;
}

string Book::get_name()
{
	return name;
}

string Book::get_author()
{
	return author;
}

int Book::get_year()
{
	return year; 
}
//modificatori
void Book::set_name(string N)
{
	name=N;
}

void Book::set_author(string K)
{
	author=K;
}

void Book::set_year(int S)
{
	year=S;
}

void Book::show()
{
	cout<<"name :"<<name<<endl;
	cout<<"author :"<<author<<endl;
	cout<<"year :"<<year<<endl;
}

Book make_book()
{
	string n,a;
	int y;
	cout << "name and author: "<<endl;
	cin >> n >> a;
	cout << "year: "<<endl;
	cin >> y;
	Book t(n,a,y);
	return t;
}
void print_book(Book t)
{
	t.show();
}

int main()
{
	Book t1;
	t1.show();
	Book t2("crocodilo bombardiro", "italian brainrot", 2025);
	t2.show();
	Book t3 = t2;
	t3.set_name("megafon telefon Gianluigi Buffon");
	t3.set_author("wtf is this");
	t3.set_year(2024);
	print_book(t3);
	t1 = make_book();
	t1.show();
	return 0;
}