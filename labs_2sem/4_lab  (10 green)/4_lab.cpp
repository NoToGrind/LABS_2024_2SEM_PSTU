//1 Вариант
#include <iostream>
using namespace std;
int main()
{
	int n;
	int ydal, dobav, ch;
	cin >> n;
	int* m = new int[n];
	cout << endl;
	for (int i = 0;i < n;i++) { cin >> m[i]; }
	cout << endl;


	cout << "Удалить элеммент (от 0): ";
	cin >> ydal;

	if (ydal >= 0 && ydal < n)
	{
		for (int i = ydal;i < n;i++)
		{
			m[i] = m[i + 1];
		}
		n--;
	}
	else { cout << "error"; }

	for (int i = 0;i < n;i++) { cout << m[i]; }
	cout << endl;

	cout << "Добавть элемент (от 0): ";
	cin >> dobav;
	cout << "Элемент: ";
	cin >> ch;

	int* nm = new int[n + 1];

	for (int i = 0;i < n + 1;i++)
	{
		if (i == dobav) { nm[i] = ch; }
		else if (i > dobav) { nm[i] = m[i - 1]; }
		else { nm[i] = m[i]; }
	}

	for (int i = 0;i < n + 1;i++) { cout << nm[i]; }
	cout << endl;

	delete[] m;
	delete[] nm;

	return 0;

}