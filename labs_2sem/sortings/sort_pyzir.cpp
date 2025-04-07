#include <iostream>
#include <cstdlib>
using namespace std;
int main()
{
    int r, range_min, range_max, tmp;
	srand(time(0));
	const int n = 10;
	int arr[n];
	range_min = 2;
	range_max = 280000;
	for (int i = 0; i < n; i++)
	{
		arr[i] = ((double)rand() / RAND_MAX) * (range_max -range_min) + range_min;
			cout << arr[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < n-1 ; i++)
	{
		for (int j = 0; j < n-1-i ; j++)
		{
			if (arr[j] > arr[j+1])
				{
					tmp = arr[j];
					arr[j]= arr[j+1];
					arr[j+1] = tmp;
				}
		}
	}

	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	return 0;
}