// ****************************************
// Program Title: Lab 02 - Exercise 1
// Project File: lab02_exercise1.cpp
// Name: David Thornton
// Course Section: CPE-435, SP 2021
// Due Date: 01/25/2021
// ****************************************

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

#define CHILDADD 2 // given
#define PARENTADD 5 // given

int main()
{
	int val = 0;
	val = fork();
	
	if(val == 0)
	{
		val += CHILDADD;
		cout << "**** Child Process ****" << endl;
		cout << "Val = " << val << endl;
		cout << "Child PID = " << getpid() << endl << endl;
	}
	else
	{
		val += PARENTADD;
		cout << "**** Parent Process ****" << endl;
		cout << "Val = " << val << endl;
		cout << "Parent PID = " << getpid() << endl << endl;
	}
}
