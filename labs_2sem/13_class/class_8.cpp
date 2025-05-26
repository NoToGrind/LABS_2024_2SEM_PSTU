#include <iostream>
#include <string>
using namespace std;

const int evNothing = 0;
const int evMessage = 100;
const int cmAdd = 1;
const int cmDel = 2;
const int cmGet = 3;
const int cmShow = 4;
const int cmMake = 6;
const int cmInfo = 7;
const int cmQuit = 101;

class Employee : public Person
{
protected:
    float zp;
    string post;

public:
    Employee(void);
    Employee(string, int, float, string);
    Employee(const  Employee&);
    ~Employee(void);
    float getZp();
    string getPost();
    void setZp(float);
    void setPost(string);
    void show();
    void input();
    Employee& operator=(const  Employee&);
};

class Dialog : public Vector
{
protected:
    int EndState;

public:
    Dialog(void);
    virtual ~Dialog(void);
    virtual void GetEvent(TEvent&);
    virtual int Execute();
    virtual void HandleEvent(TEvent&);
    virtual void ClearEvent(TEvent&);
    int Valid();
    void EndExec();
};

struct TEvent
{
    int what;
    int command;
    int message;
    int a;
};

class Object
{
public:
    virtual void show() = 0;
    virtual void input() = 0;
    void HandleEvent(const TEvent&);
};

class Person : public Object
{
protected:
    std::string name;
    int age;

public:
    Person(void);
    Person(std::string, int);
    Person(const Person&);
    ~Person(void);
    std::string getName();
    int getAge();
    void setName(std::string);
    void setAge(int);
    Person& operator=(const Person&);
    void show();
    void input();
};

class Vector
{
protected:
    Object** beg;
    int size;
    int cur;

public:
    Vector(void);
    Vector(int);
    ~Vector(void);
    void Add(void);
    void Del(void);
    void Show(void);
    void Find(int);
    int operator()();
    void HandleEvent(const TEvent& event);
};

Dialog::Dialog(void) : Vector()
{
    EndState = 0;
}

Dialog::~Dialog(void)
{
}

void Dialog::GetEvent(TEvent& event)
{
    std::string OpInt = "m+-s?q";
    std::string s;
    std::string param;

    char code;
    std::cout << "(" + OpInt + ")>>\n";
    std::cin >> s;
    code = s[0];
    if (OpInt.find(code) >= 0)
    {
        event.what = evMessage;
        switch (code)
        {
        case 'm':
            event.command = cmMake;
            break;
        case '+':
            event.command = cmAdd;
            break;
        case '-':
            event.command = cmDel;
            break;
        case 's':
            event.command = cmShow;
            break;
        case 'q':
            event.command = cmQuit;
            break;
        case '?':
            event.command = cmInfo;
            break;
        }
        if (s.length() > 1)
        {
            param = s.substr(1, s.length() - 1);
            int A = atoi(param.c_str());
            event.a = A;
        }
    }
    else
    {
        event.what = evNothing;
    }
}

int Dialog::Execute()
{
    TEvent event;
    do
    {
        EndState = 0;
        GetEvent(event);
        HandleEvent(event);
    } while (!Valid());
    return EndState;
}

int Dialog::Valid()
{
    if (EndState == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void Dialog::ClearEvent(TEvent& event)
{
    event.what = evNothing;
}

void Dialog::EndExec()
{
    EndState = 1;
}

void Dialog::HandleEvent(TEvent& event)
{
    if (event.what == evMessage)
    {
        switch (event.command)
        {
        case cmMake:
            size = event.a;
            beg = new Object * [size];
            cur = 0;
            ClearEvent(event);
            break;
        case cmAdd:
            Add();
            ClearEvent(event);
            break;
        case cmDel:
            Del();
            ClearEvent(event);
            break;
        case cmShow:
            Show();
            ClearEvent(event);
            break;
        case cmQuit:
            EndExec();
            ClearEvent(event);
            break;
        case cmInfo:
            int tmp = event.a;
            Find(tmp);
            ClearEvent(event);
            break;
        }
    }
}

Employee::Employee(void) : Person()
{
   zp = 00;
   post = " ";
}

Employee::~Employee()
{
}

void  Employee::show()
{
    std::cout << " Employee :\n";
    std::cout << " name: " << name << "\n";
    std::cout << " age: " << age << "\n";
    std::cout << " zp: " << zp << "\n";
    std::cout << " post: " << post << "\n";
}

void Employee::input()
{
    std::cout << "Student name: ";
    std::cin >> name;
    std::cout << "Student age: ";
    std::cin >> age;
    std::cout << "Student zp: ";
    std::cin >> zp;
    std::cout << "Student post: ";
    std::cin >> post;
}
Employee::Employee(std::string N, int A, float Z, string P) : Person(N, A)
{
    name = N;
    age = A;
    zp = Z;
    post = P;
}

Employee::Employee(const Employee& employee)
{
    name = employee.name;
    age = employee.age;
    zp = employee.zp;
    post = employee.post;

}
Employee& Employee::operator=(const Employee& employee)
{
    if (&employee == this)
    {
        return *this;
    }
    name = employee.name;
    age = employee.age;
    zp = employee.zp;
    post = employee.post;
    return *this;
}

float Employee::getZp()
{
    return zp;
}
string Employee::getPost()
{
    return post;
}

void Employee::setZp(float value)
{
    zp = value;
}
void Employee::setPost(string value)
{
    post = value;
}

Person::Person(void)
{
    name = "";
    age = 0;
}

Person::Person(std::string N, int A)
{
    name = N;
    age = A;
}

Person::Person(const Person& person)
{
    name = person.name;
    age = person.age;
}

Person::~Person(void)
{
}

std::string Person::getName()
{
    return name;
}

int Person::getAge()
{
    return age;
}

void Person::setName(std::string value)
{
    name = value;
}

void Person::setAge(int value)
{
    age = value;
}

Person& Person::operator=(const Person& person)
{
    if (&person == this)
    {
        return *this;
    }
    name = person.name;
    age = person.age;
    return *this;
}

void Person::show()
{
    std::cout << "Person:\n";
    std::cout << " name: " << name << "\n";
    std::cout << " age: " << age << "\n";
}

void Person::input()
{
    std::cout << "Person name: ";
    std::cin >> name;
    std::cout << "Person age: ";
    std::cin >> age;
}

Vector::Vector(void)
{
    beg = nullptr;
    size = 0;
    cur = 0;
}
Vector::Vector(int n)
{
    beg = new Object * [n];
    cur = 0;
    size = n;
}
Vector::~Vector(void)
{
    if (beg != 0)
    {
        delete[] beg;
    }
    beg = 0;
}
void Vector::Add()
{
    Object* p;

    std::cout << "1.Person\n";
    std::cout << "2.Employee\n";
    std::cout << "choose (1/2) >> ";
    int y;
    std::cin >> y;

    if (y == 1)
    {
        Person* a = new (Person);
        a->input();
        p = a;
        if (cur < size)
        {
            beg[cur] = p;
            cur++;
        }
    }
    else if (y == 2)
    {
        Employee* b = new (Employee);
        b->input();
        p = b;
        if (cur < size)
        {
            beg[cur] = p;
            cur++;
        }
    }
    else
    {
        return;
    }
}

void Vector::Show()
{
    if (cur == 0)
    {
        std::cout << "\nEmpty\n";
    }
    Object** p = beg;
    for (int i = 0; i < cur; ++i)
    {
        (*p)->show();
        p++;
    }
}

int Vector::operator()()
{
    return cur;
}

void Vector::Del(void)
{
    if (cur == 0)
    {
        return;
    }
    cur--;
}

void Vector::Find(int tmp)
{
    Object** p = beg;
    for (int i = 0; i < cur; ++i)
    {
        if (i == tmp - 1)
        {
            (*p)->show();
        }
        p++;
    }
}
void Vector::HandleEvent(const TEvent& event)
{
    if (event.what == evMessage)
    {
        Object** p = beg;
        for (int i = 0; i < cur; ++i)
        {
            (*p)->show();
            ++p;
        }
    }
}

int main()
{
    Person* p = new Person;
    p->input();
    p->show();
    Employee* s = new Employee;
    s->input();
    s->show();
    Vector t(10);
    Object* o = p;
    t.Add();
    o = s;
    t.Show();
    t.Del();
    std::cout << "\nVector: " << t() << '\n';
    Dialog D;
    D.Execute();
    return 0;
}