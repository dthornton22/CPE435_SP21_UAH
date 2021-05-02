// ****************************************
// Program Title: Lab 04
// Project File: processB.c
// Name: David Thornton
// Course Section: CPE-435, SP 2021
// Due Date: 02/08/2021
// ****************************************

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "header.h"

int main(void)
{
	int id;
	struct info* ctrl;

	if ((id = shmget(KEY, SEGSIZE, 0)) < 0)
	{
		printf("Error! Exiting program...\n");
		exit(1);
	}
	
	ctrl = (struct info*) shmat(id, 0, 0);

	if (ctrl <= (struct info*)(0))
	{
		printf("Error! Exiting program...\n");
		exit(2);
	}

	while(ctrl->flag == 0);
	ctrl->sum = ctrl->num1 + ctrl->num2; // calculate and store sum
	printf("****** Begin Process B ******\n");
	printf("Sum of %i and %i = %i\n\n", ctrl->num1, ctrl->num2, ctrl->sum);

	ctrl->flag = 0; // set the flag for process A
	while(ctrl->flag != -1); // wait for process A to set flag to -1
	shmdt(ctrl);
	exit(0);
}
