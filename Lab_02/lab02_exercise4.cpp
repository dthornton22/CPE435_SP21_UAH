// ****************************************
// Program Title: Lab 02 - Exercise 4
// Project File: lab02_exercise4.cpp
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

int main ()
{
	cout << "**** Beginning Orphan Process ****" << endl;
	int val = 0;
	val = fork();
	
	if (val == 0)
	{
		cout << "Child PID = " << getpid() << endl;
		cout << "Child PPID = " << getppid() << endl;
		wait(0);
	}
	else
	{
		cout << "Parent PID = " << getpid() << endl;
		exit(0);
	}
	wait(0); // wait for orphan process to end
	
	cout << endl << "**** Beginning Zombie Process ****" << endl;
	int val2 = fork();
	if (val2 == 0)
	{
		cout << "Child PID = " << getpid() << endl;
		exit(0);
	}
	else
	{
		cout << "Parent PID = " << getpid() << endl;
		wait(0);
	}
	wait(0); // wait for zombie process to end
	
	cout << endl << "**** Beginning Sleeping Beauty Process ****" << endl;
	cout << "Sleeping Beauty PID = " << getpid() << endl;
	wait(0); // wait for sleeping beauty process to end
	
	cout << "Ending program..." << endl;
}
