// ****************************************
// Program Title: Lab 09
// Project File: merge_sort.cpp
// Name: David Thornton
// Course Section: CPE-435, SP 2021
// Due Date: 03/15/2021
// ****************************************
#include "sorts.h"

void mergeRunner(int size, int arr[])
{
	time_t start = time(0);
	mergeSort(arr, 0, size - 1); // do the sort
	time_t end = time(0);
	double time = difftime(end, start);
	cout << "Merge sort took " << time << " seconds." << endl;
}



void mergeSort(int arr[], int l, int r)
{
	if (l >= r)
	{
		return;
	}
	int m = l + (r - l) / 2;
	mergeSort(arr, l, m);
	mergeSort(arr, m + 1, r);
	merge(arr, l, m, r);
}



void merge(int arr[], int l, int m, int r)
{
	int n1 = m - l + 1;
	int n2 = r - m;
	int* L = new int[n1];
	int* R = new int[n2];
	for (int i = 0; i < n1; i++)
	{
		L[i] = arr[l + i];
	}
	for (int j = 0; j < n2; j++)
	{
		R[j] = arr[m + 1 + j];
	}
	int i = 0;
	int j = 0;
	int k = l;
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}
