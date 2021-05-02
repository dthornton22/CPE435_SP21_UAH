// ****************************************
// Program Title: Lab 09
// Project File: insertion_sort.cpp
// Name: David Thornton
// Course Section: CPE-435, SP 2021
// Due Date: 03/15/2021
// ****************************************
#include "sorts.h"

void insertRunner(int size, int arr[])
{
	time_t start = time(0);
	insertionSort(arr, size); // do the sort
	time_t end = time(0);
	double time = difftime(end, start);
	cout << "Insertion sort took " << time << " seconds." << endl;
}



void insertionSort(int arr[], int n)
{
	int i, key, j;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}
