#include <iostream>
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


void bucketSort(int arr[], int length) {
	int buckets[10][10];
	int bucketSizes[10] = { 0 };
	for (int i = 0; i < length; i++) {
		int bucketIndex = arr[i] / 10;
		buckets[bucketIndex][bucketSizes[bucketIndex]] = arr[i];
		bucketSizes[bucketIndex]++;
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 1; j < bucketSizes[i]; j++) {
			int temp = buckets[i][j];
			int k = j - 1;
			while (k >= 0 && buckets[i][k] > temp) {
				buckets[i][k + 1] = buckets[i][k];
				k--;
			}
			buckets[i][k + 1] = temp;
		}
	}

	int index = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < bucketSizes[i]; j++) {
			arr[index++] = buckets[i][j];
		}
	}
	for (int i = 0; i < length; i++) { cout << arr[i] << " "; }
}
int main()
{
	setlocale(LC_ALL, "rus");
	int const n = 10;
	int arr[n];
	cout << "Текущий массив:" << endl;
	createArray(arr, n);
	cout << "Отсортированный массив:" << endl;
	bucketSort(arr, n);
	return 0;
}