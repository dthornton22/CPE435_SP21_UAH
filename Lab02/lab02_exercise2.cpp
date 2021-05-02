// ****************************************
// Program Title: Lab 02 - Exercise 2
// Project File: lab02_exercise2.cpp
// Name: David Thornton
// Course Section: CPE-435, SP 2021
// Due Date: 01/25/2021
// ****************************************

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

void child1(int num1, int num2); // Function prototype

int main()
{
  	srand (time(NULL)); // initialize random seed for numbers
	int num1 = rand() % 100;
	int num2 = rand() % 100;
	
 	int val = 0;
	val = fork(); // Start child 1
	
	if (val == 0)
	{
		child1(num1, num2);
	}
	else
	{
		cout << "**** Parent Process ****" << endl;
		cout << "Parent PID = " << getpid() << endl << endl;
		wait(0);
		cout << "\n**** Parent Process ****" << endl;
		cout << "Ending program..." << endl;
		cout << "************************" << endl;
		exit(0);
		// return 0;
	}
}

void child1(int num1, int num2)
{
	int subResult = num1 - num2;
	int addResult = num1 + num2;
	int mulResult = num1 * num2;
	
	cout << "**** Child 1 Process ****" << endl;
	cout << "Child1 PID = " << getpid() << endl;
	cout << "Result of " << num1 << " - " << num2 << " = " << subResult << endl;

	int child1val = 0;
	child1val = fork(); // start child 2
	
	if (child1val == 0)
	{
		cout << "\n**** Child 2 Process ****" << endl;
		cout << "Child2 PID = " << getpid() << endl;
		cout << "Result of " << num1 << " + " << num2 << " = " << addResult << endl;
		exit(0);
	}
	else
	{
		wait(0); // wait for child2 to finish
		cout << "\n**** Child 1 Process ****" << endl;
		cout << "Result of " << num1 << " * " << num2 << " = " << mulResult << endl;
		exit(0);
	}
}
