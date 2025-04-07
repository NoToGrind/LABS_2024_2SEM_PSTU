#include <iostream>
#include <cstdlib>
using namespace std;

float sum(double a, double b)
{
	return a + b;
}

float sum(double cA, double zA, double cB, double zB)
{
	
	return (cA * zB + cB * zA) / (zA * zB);
	
}

void main()
{
	setlocale(LC_ALL, "rus");
	double a, b;
	cout << "ВВедите два числа:" << endl;
	cin >> a >> b;
	double result1 = sum(a, b);
	cout << "Сумма двух вещественных чисел равна:" << result1 << endl;

	double cA, zA, cB, zB;
	cout << "Введите числитель первой дроби:" << endl;
	cin >> cA;
	cout << "Введите знаменатель первой дроби:" << endl;
	cin >> zA;
	cout << "Введите числитель второй дроби:" << endl;
	cin >> cB;
	cout << "Введите знаменатель второй дроби:" << endl;
	cin >> zB;
	float result2 = sum( cA, zA, cB, zB);
	cout << "Сумма обыкновенных дробей равна:" <<result2<< endl;
	
}