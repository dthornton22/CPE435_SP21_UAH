// ****************************************
// Program Title: Lab 02 - Exercise 3
// Project File: lab02_exercise3.cpp
// Name: David Thornton
// Course Section: CPE-435, SP 2021
// Due Date: 01/25/2021
// ****************************************

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>

using namespace std;

int main (int argc, char* argv[])
{
	if(argv[1] == NULL)
	{
		cout << "*************** ERROR ***************" << endl;
		cout << "Please enter a number as a paramter." << endl;
		cout << "Exiting program..." << endl;
		cout << "************ END OF ERROR ***********" << endl;
		exit(0);
	}

	int num = atoi(argv[1]); // a to i function is a string parser from stdlib.h
	
	if (num%2 == 0)
	{
		int count = log2(num); // need log2 because there are 2^n processes
		cout << "Executing for loop " << count << " times" << endl;
		
		for (int i = 0; i < count; i++)
		{
			int val = 0;
			val = fork();
			if (val == 0)
			{
				cout << "Child ID = " << getpid() << endl;
			}

		}
		exit(0);
	}
	else if (num%2 != 0)
	{
		cout << "*************** ERROR ***************" << endl;
		cout << "Input was an odd number" << endl;
		cout << "Please try an even number" << endl;
		cout << "************ END OF ERROR ***********" << endl;
		cout << "Ending Program..." << endl;
		exit(0);
	}
	exit(0);
}
