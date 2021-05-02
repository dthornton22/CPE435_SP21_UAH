// ****************************************
// Program Title: Lab 09
// Project File: quick_sort.cpp
// Name: David Thornton
// Course Section: CPE-435, SP 2021
// Due Date: 03/15/2021
// ****************************************
#include "sorts.h"

void quickRunner(int size, int arr[])
{
	time_t start = time(0);
	quickSort(arr, 0, size - 1);
	time_t end = time(0);
	double time = difftime(end, start);
	cout << "Quick sort took " << time << " seconds." << endl;
}



void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}



int partition(int arr[], int low, int high)
{
	int pivot = arr[high];
	int i = (low - 1);
	for (int j = low; j <= high - 1; j++)
	{
		if (arr[j] < pivot)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}



void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}
