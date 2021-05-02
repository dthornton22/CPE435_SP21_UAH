// ****************************************
// Program Title: Lab 09
// Project File: sorts.h
// Name: David Thornton
// Course Section: CPE-435, SP 2021
// Due Date: 03/15/2021
// ****************************************
// C++ program for insertion sort	adapted from GeeksforGeeks - rathbhupendra
// C++ program for quick sort		adapted from GeeksforGeeks - rathbhupendra
// C++ program for merge sort		adapted from GeeksforGeeks - Mayank Tyagi

#ifndef SORTS
#define SORTS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

// Sorting functions
void quickSort(int arr[], int low, int high);
int partition(int arr[], int low, int high);
void merge(int arr[], int l, int m, int r);
void mergeSort(int arr[], int l, int r);
void insertionSort(int arr[], int n);
void swap(int* a, int* b);

// Runner and verify functions
void insertRunner(int size, int arr[]);
void mergeRunner(int size, int arr[]);
void quickRunner(int size, int arr[]);
bool verify(int size, int arr[]);

#endif
