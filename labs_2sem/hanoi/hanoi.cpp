#include <iostream>
using namespace std;
void hanoi_town(int n, char st, char fin, char tmp)
{
    if (n == 1) {
        
        cout << "Первый диск движется из " << st
            << " в стержень " << fin << endl;
        return;
    }
    hanoi_town(n - 1, st, tmp, fin);

    cout << "Движение диска " << n << " из стержня " << st
        << " в стержень " << fin << endl;
    hanoi_town(n - 1, tmp, fin, st);
}

int main()
{
    
    int n = 3;
    Han_town(n, 'A', 'C', 'B');

    return 0;
}