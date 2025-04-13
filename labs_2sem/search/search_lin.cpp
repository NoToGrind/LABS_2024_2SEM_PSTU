#include <iostream>
using namespace std;
int search(int arr[], int n, int x)
{
	for (int i = 0; i < n; i++)
	{
		if (arr[i] == x) return i;
	}
	return -1;
}

int main()
{
	setlocale(LC_ALL, "ru");
	int arr[10] = { 1, 4, 4, 5, 12, 13, 15, 21, 21, 44 };
	int arrLength = sizeof(arr) / sizeof(arr[0]);
	int x = 12;
	int res = search(arr, arrLength, x);
	if (res == -1) cout << "Элемент " << x << " не найден" << endl;
	else cout << "Элемент " << x << " найден по индексу " << res <<
		endl;
	return 0;
}