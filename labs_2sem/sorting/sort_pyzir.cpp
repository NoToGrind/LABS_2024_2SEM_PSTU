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

	int res,k;
	bool fl = true;
	while (fl)
	{
		k = 0;
		for (int i = 0;i < n - 1;i++)
			if (m[i] > m[i + 1])
			{
				res = m[i];
				m[i] = m[i + 1];
				m[i + 1] = res;
				k = 1;
			}
		if (k == 0) { fl = false; }
	}

	for (int i = 0;i < n - 1;i++) { cout << m[i] << " "; }

    return 0;
}