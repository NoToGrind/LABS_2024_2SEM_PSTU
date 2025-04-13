#include <iostream>
using namespace std;

class Fraction {
private:
    unsigned int first;   
    unsigned int second;  

public:
    Fraction(unsigned int f, unsigned int s) {
        if (s == 0) {
            cout << "detorminator cant be 0" << endl;
            // Так как мы не используем исключения, просто установим знаменатель 1
            second = 1;
        } else {
            second = s;
        }
        first = f;
    }

    // Метод для получения целой части дроби
    unsigned int ipart() const {
        return first / second;
    }

    // Методы для доступа к полям
    unsigned int getFirst() const { return first; }
    unsigned int getSecond() const { return second; }
};

int main() {
    
    Fraction f1(7, 2);
    cout << "Fraction " << f1.getFirst() << "/" << f1.getSecond() 
              << " has integer part: " << f1.ipart() << endl;

    Fraction f2(5, 0);
    cout << "Fraction " << f2.getFirst() << "/" << f2.getSecond() 
              << " has integer part: " << f2.ipart() << endl;

    return 0;
}