// ****************************************
// Program Title: Lab 08
// Project File: question1.c
// Name: David Thornton
// Course Section: CPE-435, SP 2021
// Due Date: 03/09/2021
// ****************************************

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

pid_t pid = 0;
void kill_func(int killSignal);
void child_kill_func(int killSignal);
void myFunction(int sigVal);
void printProtect(int sigVal);

int main()
{
	pid = fork();
	if(pid == 0) // child
	{
		signal(SIGINT, printProtect);
		signal(SIGTERM, child_kill_func);
		while(1);
	}
	else // parent
	{
		signal(SIGINT, printProtect);
		signal(SIGALRM, myFunction);
		alarm(10);
		while(1);
	}
	while(1);
	return(0);
}


void kill_func(int killSignal)
{
	printf("Received kill signal %d\n", killSignal);
	printf("Killing child process...\n");
	kill(pid, SIGTERM);
	wait(0);
	printf("Child process killed\n");
	printf("\tDying process %d\n", getpid());
	exit(0);
}


void child_kill_func(int killSignal)
{
	printf("Requested termination from parent process\n");
	printf("\tDying process %d\n", getpid());
	exit(0);
}


void myFunction(int sigVal)
{
	printf("Program can now be terminated...\n");
	signal(SIGINT, kill_func);
}


void printProtect(int sigVal)
{
	if(pid == 0) // child
	{
		return;
	}
	else if (pid > 0)
	{
		printf("\nDetected SIGINT in process %d. System is still protected!\n", getpid());
	}
}
