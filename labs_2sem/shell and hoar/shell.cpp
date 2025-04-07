#include <iostream>
using namespace std;

void shellSort(int arr[], int n)
{

    for (int h = n / 2; h > 0; h /= 2)
    {

        for (int i = h; i < n; i++)
        {
            int tmp = arr[i];
            int j;
            for (j = i; j >= h && arr[j - h] > tmp; j -= h)
            {
                arr[j] = arr[j - h];
            }
            arr[j] = tmp;
        }
    }

    for (int i = 0; i < n; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    int arr[5] = { 6, -8, 4, -1, 2 };
    int n = sizeof(arr) / sizeof(arr[0]);
    shellSort(arr, n);
}