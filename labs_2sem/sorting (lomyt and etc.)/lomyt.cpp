#include <iostream>
using namespace std;

void createArray(int arr[], int size) 
{
    srand(time(0));
    if (size >= 2) 
    {
        for (int i = 0; i < size; i++) 
        {
            arr[i] = rand() % 100;
        }
    }
    else 
    {
        cout << "Error (size)" << endl;
        exit(0);
    }

    for (int i = 0; i < size; i++)
    { 
        cout << arr[i] << " "; 
    }
    cout << endl;
}

int quickSort(int arr[], int startElem, int endElem)
{
    int pivot = arr[endElem];
    int pivIndex = startElem;
    for (int i = startElem; i < endElem; i++) 
    {
        if (arr[i] <= pivot) {
            swap(arr[i], arr[pivIndex]);
            pivIndex++;
        }
    }
    swap(arr[pivIndex], arr[endElem]);
    return pivIndex;
}

void LomutoSort(int arr[], int start, int end) 
{
    if (start >= end)  return;
    int pivot = quickSort(arr, start, end);
    LomutoSort(arr, start, pivot - 1);
    LomutoSort(arr, pivot + 1, end);
}

int main()
{
    setlocale(LC_ALL, "ru");
    int const n = 10; 
    int arr[n];
    cout << "Данный массив:" << endl;
    createArray(arr, n);
    cout << "Отсортированный массив:" << endl;
    LomutoSort(arr, 0, n - 1);
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " "; 
    }
    return 0;
}