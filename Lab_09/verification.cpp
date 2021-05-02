// ****************************************
// Program Title: Lab 09
// Project File: verification.cpp
// Name: David Thornton
// Course Section: CPE-435, SP 2021
// Due Date: 03/15/2021
// ****************************************
#include "sorts.h"

using namespace std;

int main(int argc, char* argv[])
{
	int mergeArraySize = atoi(argv[1]); // # of ints to generate, default 50000000
	int insertArraySize = mergeArraySize / 300; // insert takes too long
	int quickArraySize = mergeArraySize * 1.5; // quick is too quick
	srand((unsigned int)time(NULL)); // seed for random number generation

	int* array1 = new int[insertArraySize]; // allocate heap memory
	for (int i = 0; i < insertArraySize; i++)
	{
		array1[i] = rand();
	}
	cout << "*********************************************" << endl;
	cout << "Starting insertion sort for "<< insertArraySize << " elements" << endl;
	insertRunner(insertArraySize, array1);
	bool insertVerify = verify(insertArraySize, array1);
	if (!insertVerify)
	{
		cout << "Insertion sort failed!!!" << endl;
	}
	else if (insertVerify)
	{
		cout << "Insertion sort was successful." << endl;
	}
	cout << "*********************************************" << endl;
	delete[] array1;
	array1 = NULL;

	cout << "Starting merge sort for " << mergeArraySize << " elements" << endl;
	int* array2 = new int[mergeArraySize]; // allocate heap memory
	for (int i = 0; i < mergeArraySize; i++)
	{
		array2[i] = rand();
	}
	mergeRunner(mergeArraySize, array2);
	bool mergeVerify = verify(mergeArraySize, array2);
	if (!mergeVerify)
	{
		cout << "Merge sort failed!!!" << endl;
	}
	else if (mergeVerify)
	{
		cout << "Merge sort was successful." << endl;
	}
	cout << "*********************************************" << endl;
	delete[] array2;
	array2 = NULL;

	cout << "Starting quick sort for " << quickArraySize << " elements" << endl;
	int* array3 = new int[quickArraySize]; // allocate heap memory
	for (int i = 0; i < quickArraySize; i++)
	{
		array3[i] = rand();
	}
	quickRunner(quickArraySize, array3);
	bool quickVerify = verify(quickArraySize, array3);
	if (!quickVerify)
	{
		cout << "Quick sort failed!!!" << endl;
	}
	else if (quickVerify)
	{
		cout << "Quick sort was successful." << endl;
	}
	cout << "*********************************************" << endl;
	delete[] array3;
	array3 = NULL;
	cout << "End of program" << endl;
	return 0;
}



bool verify(int size, int array[])
{
	for (int i = 0; i < size - 1; i++)
	{
		if (array[i] > array[i + 1])
		{
			return false;
		}
	}
	return true;
}
