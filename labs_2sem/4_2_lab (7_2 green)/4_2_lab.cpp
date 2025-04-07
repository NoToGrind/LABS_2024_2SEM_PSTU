#include <iostream>
#include <cstdarg>
using namespace std;

float product(int count, ...)
{
    float result = 1;

    va_list args;
    va_start(args, count); // Инициализируем список аргументов

    for (int i = 0; i < count; ++i)
    {
        float number = va_arg(args, int); // Получаем следующий аргумент
        result *= number; // Умножаем на каждый аргумент
    }

    va_end(args); // Завершаем работу с аргументами

    return result;
}

int main()
{
    cout << product(3, 4, 6, 12 ) << endl;
    cout << product(7, 8, 5, 6,20, 10, 9, 2) << endl;
    cout << product(11, 8, 5, 6, 20, 10, 9, 2, 3, 3, 7, 11, 23) << endl;
}