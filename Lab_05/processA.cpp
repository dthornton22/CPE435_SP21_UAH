// ****************************************
// Program Title: Lab 05
// Project File: processA.c
// Name: David Thornton
// Course Section: CPE-435, SP 2021
// Due Date: 02/17/2021
// ****************************************
#include <stdio.h> 
#include <ctype.h>
#include <string.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <stdlib.h>
#include "header.h"

void exitProcess(int msgid);

int main()
{
	struct text_message message;
	int msgid = msgget(key, 0666 | IPC_CREAT);
	while(1) // Infinite loop
	{
		printf("Process A Write Data: ");
		fgets(message.mesg_text, MAX, stdin);
		message.mesg_type = 1;
		msgsnd(msgid, &message, sizeof(message), 0);
		if(strcmp(message.mesg_text, "Exit\n") == 0)
		{
			exitProcess(msgid);
		}
		printf("Process A Data send is: %s", message.mesg_text);
		
		msgrcv(msgid, &message, sizeof(message), 2, 0);
		if(strcmp(message.mesg_text, "Exit\n") == 0)
		{
			exitProcess(msgid);
		}
		printf("Data Received from Process B is: %s", message.mesg_text);
	}
	msgctl(msgid, IPC_RMID, 0);
	return 0;
}

void exitProcess(int msgid)
{
	printf("*********************************");
	printf("\nExiting both processes now...\n");
	printf("********************************\n");
	msgctl(msgid, IPC_RMID, 0);
	exit(0);
}
