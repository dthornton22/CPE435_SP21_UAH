// ****************************************
// Program Title: Lab 07
// Project File: pbs.c
// Name: David Thornton
// Course Section: CPE-435, SP 2021
// Due Date: 03/01/2021
// ****************************************
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

struct process
{
	int pid;
	int priority;
	int burst_time;
	int working_time;
	int t_round; // turn around time
	int wait_time; // Wait Time = Turn around Time - Burst Time
};

int main(int argc, char* argv[])
{
	//Assuming ./prio n qtu pid0 pbt0 priority0 pid1 pbt1 priority1 ...

	int n = atoi(argv[1]); // number of processes
	int qtu = atoi(argv[2]); // quantum time unit
	int pid_and_pbt[n];
	int avgwait = 0;
	int count = 0;
	int count2 = 0;
	struct process *processes;
	
	for (int i = 3; i < argc; i++)
	{
		pid_and_pbt[i-3] = atoi(argv[i]);
	}
	
	// Allocating memory for n number of processes
	processes = malloc(sizeof(struct process) * n);
	
	if (processes == NULL)
	{
		printf("******** ERROR ********\n");
		printf("Memory allocation error\n");
		printf("Exiting now...\n");
		exit(1);
	}
	
	// Move values from pid_and_pbt[] to processes[]
	for (int i = 0; i < n; i++)
	{
		processes[i].pid = pid_and_pbt[i+count];
		processes[i].burst_time = pid_and_pbt[i+count+1];
		processes[i].priority = pid_and_pbt[i+count+2];
		count += 2;
	}

	// sort processes by priority using qsort

	// Finding waiting times

	for (int i = 0; i < n; i++)
	{
		if (processes[i].priority == n - count2)
		{
			processes[i].wait_time = processes[i+count2].burst_time + processes[i+count2].wait_time;
			count2++;
			i = 0;
		}
	}

	// Finding average wait time
	for (int i = 0; i < n; i++)
	{
		avgwait += processes[i].wait_time;
	}
	avgwait = avgwait / n;
	
	// Finding turn around times
	for (int i = 0; i < n; i++)
	{
		processes[i].t_round = processes[i].burst_time + processes[i].wait_time;
	}

	// Print results
	for (int i = 0; i < n; i++)
	{
		printf("Process: %d\n", i);
		printf("\tPID: %d\n", processes[i].pid);
		printf("\tPBT: %d\n", processes[i].burst_time);
		printf("\tTurn Around Time: %d\n", processes[i].t_round);
		printf("\tWait Time: %d\n", processes[i].wait_time);
		printf("\tPriority: %d\n\n", processes[i].priority);
	}
	printf("\nQuantum Time Unit: %d\n", qtu);
	printf("Average Wait Time: %d\n", avgwait);
	void free(void*);
}
