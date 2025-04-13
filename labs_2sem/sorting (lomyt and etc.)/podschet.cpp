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


void countSort(int arr[], int length) 
{
    int* countArr = new int[length];
    int max = arr[0];

    for (int i = 1; i < length; i++) 
    {
        if (arr[i] > max) 
        { 
            max = arr[i]; 
        }
    }
    int* count = new int[max + 1];

    for (int i = 0; i <= max; ++i) 
    {
        count[i] = 0;
    }

    for (int i = 0; i < length; i++)
    {
        count[arr[i]]++;
    }

    for (int i = 1; i <= max; i++) 
    {
        count[i] += count[i - 1];
    }
    for (int i = length - 1; i >= 0; i--) 
    {
        countArr[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    for (int i = 0; i < length; i++)
    {
        arr[i] = countArr[i];
    }
    delete[] count;
    delete[] countArr;

    for (int i = 0; i < length; i++) 
    {
        cout << arr[i] << " "; 
    }
}
int main()
{
    setlocale(LC_ALL, "ru");
    int const n = 10;
    int arr[n];
    cout << "Данный массив: " << endl;
    createArray(arr, n);
    cout << "Отсортированный массив: " << endl;
    countSort(arr, n);
    return 0;
}