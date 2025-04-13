#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;
void createArray(int arr[], int size) {
    srand(time(0));
    if (size >= 2) {
        for (int i = 0; i < size; i++) {
            arr[i] = rand() % 100;
        }
    }
    else {
        cout << "Error (size)" << endl;
        exit(0);
    }

    for (int i = 0; i < size; i++) { cout << arr[i] << " "; } cout << endl;
}

void merge(int arr[], int leftPart, int midPart, int rightPart) { //сливаем
    int leftRange = midPart - leftPart + 1;
    int rightRange = rightPart - midPart;

    int* leftArr = new int[leftRange];
    int* rightArr = new int[rightRange];

    for (int i = 0; i < leftRange; i++) { leftArr[i] = arr[leftPart + i]; }
    for (int i = 0; i < rightRange; i++) { rightArr[i] = arr[midPart + 1 + i]; }

    int leftIndex = 0;
    int rightIndex = 0;
    int mergeIndex = leftPart;

    while (leftIndex < leftRange && rightIndex < rightRange) {
        if (leftArr[leftIndex] <= rightArr[rightIndex]) {
            arr[mergeIndex] = leftArr[leftIndex];
            leftIndex++;
        }
        else {
            arr[mergeIndex] = rightArr[rightIndex];
            rightIndex++;
        }
        mergeIndex++;
    }

    while (leftIndex < leftRange) {
        arr[mergeIndex] = leftArr[leftIndex];
        leftIndex++;
        mergeIndex++;
    }
    while (rightIndex < rightRange) {
        arr[mergeIndex] = rightArr[rightIndex];
        rightIndex++;
        mergeIndex++;
    }

    delete[] leftArr;
    delete[] rightArr;
}

void mergeSort(int arr[], int start, int end) { //делим
    if (start >= end) { return; }

    int mid = start + (end - start) / 2;
    mergeSort(arr, start, mid);
    mergeSort(arr, mid + 1, end);
    merge(arr, start, mid, end);
}

int main()
{
    setlocale(LC_ALL, "ru");
    int const n=10;
    int arr[n];
    cout << "Массив:" << endl;
    createArray(arr, n);
    cout << "Oтсортированный Массив:" << endl;
    mergeSort(arr, 0, n - 1);
    for (int i = 0; i < n; i++)
    { 
        cout << arr[i] << " "; 
    }
    return 0;
}