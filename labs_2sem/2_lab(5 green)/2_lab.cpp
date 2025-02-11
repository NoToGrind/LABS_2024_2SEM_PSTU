//Вариант 24
#include <iostream>
using namespace std;

int main()
{
	const int n = 3;
	int m[n][n] = {{1,3,4},
			{ 3,3,5 },
			{ 7,1,2 } };
	int k = 0;
	for (int i=0;i<n;i++)
		for (int j = 0;j < n;j++)
		{ 
			if (m[i][j] > m[2][2]) //сравнение с элементом с индексом [2][2], стоящим на главной диагонали, сравниваются все числа, включая гл диагональ
				k++;
		}

	cout << k;

	return 0;
}