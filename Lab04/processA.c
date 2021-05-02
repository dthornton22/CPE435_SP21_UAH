// ****************************************
// Program Title: Lab 04
// Project File: processA.c
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

	if ((id = shmget(KEY, SEGSIZE, IPC_CREAT | 0666)) < 0)
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

	ctrl->num1 = 420;
	ctrl->num2 = 69;
	ctrl->flag = 1;
	printf("****** Begin Process A ******\n");
	printf("Set Number 1 = %i\n", ctrl->num1);
	printf("Set Number 2 = %i\n", ctrl->num2);
	printf("Set Flag = %i\n\n", ctrl->flag);
	fflush(stdout);

	while(ctrl->flag != 0); // wait for flag to get set by process B

	ctrl->flag = -1;
	printf("Set flag to %i\n", ctrl->flag);
	printf("Terminating program...\n");
	fflush(stdout);
	shmdt(ctrl);
	shmctl(id,IPC_RMID,NULL);
	exit(0);
}
