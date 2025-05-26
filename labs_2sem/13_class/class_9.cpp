#include <iostream>
using namespace std;

const int MAX_SIZE = 20;

class Vector
{
    int size;
    int* last;
public:
    Vector() { size = 0; last = 0; }
    Vector(int s);
    Vector(int s, int* mas);
    Vector(const Vector& v);
    ~Vector();
    const Vector& operator=(const Vector& v);
    int& operator[](int i);
    operator int() const { return size; }
    Vector operator+(int n);
    Vector operator-(int n);
    Vector operator--();

    friend ostream& operator<<(ostream& out, const Vector& v);
    friend istream& operator>>(istream& in, Vector& v);
};

Vector::Vector(int s) {
    if (s > MAX_SIZE) throw 1;
    size = s;
    last = new int[s]();
    
}

Vector::Vector(const Vector& v) {
    size = v.size;
    last = new int[size];
    for (int i = 0; i < size; i++) last[i] = v.last[i];
}

Vector::~Vector() {
    delete[]last;
}

Vector::Vector(int s, int* mas) {
    if (s > MAX_SIZE) throw 1;
    size = s;
    last = new int[size];
    for (int i = 0; i < size; i++) last[i] = mas[i];
}

const Vector& Vector::operator=(const Vector& v) {
    if (this == &v) return *this;
    if (last != 0) delete[]last;
    size = v.size;
    last = new int[size];
    for (int i = 0; i < size; i++) last[i] = v.last[i];
    return *this;
}

ostream& operator<<(ostream& out, const Vector& v) {
    if (v.size == 0) out << "Empty\n";
    else {
        for (int i = 0; i < v.size; i++) out << v.last[i] << " ";
        out << endl;
    }
    return out;
}

istream& operator>>(istream& in, Vector& v) {
    for (int i = 0; i < v.size; i++) {
        cout << ">";
        in >> v.last[i];
    }
    return in;
}

int& Vector::operator[](int i) {
    if (i < 0) throw 1;
    if (i >= size) throw 2;
    return last[i];
}
Vector Vector::operator+(int n)
{
    if (n <= 0) return *this;
    if (size + n > MAX_SIZE) throw out_of_range("Exceeded MAX_SIZE");

    Vector result(size + n);
    for (int i = 0; i < size; i++) result.last[i] = last[i];
    for (int i = size; i < size + n; i++) result.last[i] = 0;

    return result;
}
Vector Vector::operator-(int n) {
    if (n <= 0) return *this;
    if (n > size) n = size;

    Vector result(size - n);
    for (int i = 0; i < size - n; i++) result.last[i] = last[i];

    return result;
}

Vector Vector::operator--()
{
    return (*this - 1);
}

int main()
{
    try
    {
        Vector v1(3);
        cout<< "v1: "<< v1;
        v1 = v1 + 2;   // добавляем 2 элемента
        cout << "v1 after +2: " << v1;  // 0 0 0 0 0
        v1[1] = 5;

        Vector v2 = v1 - 3;  // удаляем 3 элемента
        cout << "v2 (v1-3): " << v2; 

        --v2;          
        cout << "v2 after --: " << v2;  

        cout << "Size of v2: " << (int)v2 << endl;  
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}