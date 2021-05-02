// ****************************************
// Program Title: Lab 07
// Project File: rrs.c
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
	int burst_time;
	int t_round; // turn around time
	int wait_time; // Wait Time = Turn around Time - Burst Time
};

int main(int argc, char* argv[])
{
	//Assuming ./rrs n qtu pid0 pbt0 pid1 pbt1 ...

	int n = atoi(argv[1]); // number of processes
	int qtu = atoi(argv[2]); // quantum time unit
	int pid_and_pbt[n]; // array for PID and PBT values
	int avgwait = 0;
	int count = 0;
	struct process *processes;
	
	for (int i = 3; i < argc; i++)
	{
		if(i % 2 == 1) // if argv 3, 5, 7, ...
			{
				pid_and_pbt[i-3] = atoi(argv[i]);
			}
		else if(i % 2 == 0) // if argv 4, 6, 8, ...
			{
				pid_and_pbt[i-3] = atoi(argv[i]);
			}
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
		processes[i].burst_time = pid_and_pbt[i+1+count];
		count++;
	}
	
	// Finding wait times
	while (1)
	{
		bool done = false;
		for (int i = 0; i < n; i++)
		{
			int t = 0;
			if (pid_and_pbt[2*i] > 0)
			{
				done = true;
				if(pid_and_pbt[2*i] > qtu)
				{
					t += qtu;
					pid_and_pbt[2*i] -= qtu;
				}
				else
				{
					t += pid_and_pbt[i];
					processes[i].wait_time = t - processes[i].burst_time;
					pid_and_pbt[2*i] = 0;
				}
			}
		}
		if (done == true)
		{
			break;
		}
	}
	
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
		printf("\tWait Time: %d\n\n", processes[i].wait_time);
	}
	printf("\nQuantum Time Unit: %d\n", qtu);
	printf("Average Wait Time: %d\n", avgwait);
	void free(void*);
}
