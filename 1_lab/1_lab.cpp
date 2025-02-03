#include <iostream>
#include <cstdlib>
using namespace std;
int main()
{

	int r, range_min, range_max;
	const int n = 20;
	int m[n];
	range_min = 2;
	range_max = 50;
	for (int i = 0; i < n; i++)
	{
		m[i] = ((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;
		cout << m[i] << " ";
	}
	cout << endl;

	int k;
	cin >> k;
	for (int i = k;i < n;i++) 
	{ 
		if (m[i] == n - 1){break;}
		else
		{
			m[i] = m[i + 1];
		}
	}

	const int n2 = n + n;
	int newm[n2];
	int j = 0;
	for (int i = 0; i < n; i++)
	{
		newm[j] = m[i];
		j++;
		if (m[i] % 2 == 0)
		{
			newm[j] = 0;
			j++;
		}
	}

	for (int i = 0; i < j; i++) { cout << newm[i] << " "; }

    return 0;
}
