// ****************************************
// Program Title: Lab 08
// Project File: question2.c
// Name: David Thornton
// Course Section: CPE-435, SP 2021
// Due Date: 03/09/2021
// ****************************************

#define ALARM_LENGTH 10

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void kill_func(int killSignal);
void timeBomb(int sigVal);

int main()
{
	printf("Doing nothing\n");
	signal(SIGINT, timeBomb); 	// when SIGINT is recieved, call timeBomb
	while(1);
	return -1;
}


void timeBomb(int sigVal)
{
	printf("\nReceived signal: %d\n", sigVal);
	signal(SIGALRM, kill_func); 	// when SIGALRM is recieved, call kill_func
	alarm(ALARM_LENGTH);			// set alarm
	printf("Setting alarm for %d second(s).\n", ALARM_LENGTH);
	while(1)
	{
		char randomchar = 'A' + (random() % 26);
		printf("%c", randomchar); // print random char
	}
	printf("\nEnd of alarm, exiting program...\n");
	exit(1);
}


void kill_func(int killSignal)
{
	printf("\nReceived kill signal: %d\n", killSignal);
	printf("Dying process PID: %d\n", getpid());
	exit(0); // kills the process that made the function call
}
