// ****************************************
// Program Title: Lab 03
// Project File: SuperCoolShell.c
// Name: David Thornton
// Course Section: CPE-435, SP 2021
// Due Date: 02/01/2021
// ****************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define LINE_MAX 100 // how long can a line be
#define ARGS_MAX 10 // how many different commands/symbols/options

int main(int argc, char* argv[])
{
	while(1) // infinite loop
	{
		int i = 0;
		int j = 0;
		int needsRedirect = 0;
		int needsPipe = 0;
		char* temp;
		char* myBrokenArgs[ARGS_MAX];
		char* myBrokenArgs2[ARGS_MAX];
		char myString[LINE_MAX];
		char myFileName[LINE_MAX];
		
		printf("SuperCoolShell: ");
		fgets(myString, LINE_MAX, stdin); // get input line
		myString[strlen(myString) - 1] = '\0'; // replace newline char with NULL
		myBrokenArgs[0] = strtok(myString," "); // assumption in lab doc

		while(myBrokenArgs[i] != NULL) // check for input
		{
			if(myBrokenArgs[i][0] == '>') // check for output file
			{
				needsRedirect = 1;
				myBrokenArgs[i] = NULL;
				temp = strtok(NULL, ">");
				sprintf(myFileName, "%s", temp);
				break;
			}
			else if(myBrokenArgs[i][0] == '<') // check for i file
			{
				needsRedirect = 2;
				myBrokenArgs[i] = NULL;
				temp = strtok(NULL, "<");
				sprintf(myFileName, "%s", temp);
				break;
			}
			else if(myBrokenArgs[i][0] == '|') // check for piping
			{
				needsPipe = 1;
				myBrokenArgs[i] = NULL;
				myBrokenArgs2[0] = strtok(NULL, " ");
				while(myBrokenArgs2[j] != NULL) // for the 2nd command
				{
					if(myBrokenArgs2[j][0] == '>') // check for output file in pipe
					{
						needsRedirect = 1;
						myBrokenArgs2[j] = NULL;
						temp = strtok(NULL, ">");
						sprintf(myFileName, "%s", temp);
					break;
					}
					else if(myBrokenArgs2[j][0] == '<') // check for input file in pipe
					{
						needsRedirect = 2;
						myBrokenArgs2[j] = NULL;
						temp = strtok(NULL, "<");
						sprintf(myFileName, "%s", temp);
						break;
					}
					myBrokenArgs2[++j] = strtok(NULL, " ");
				}
				break;
			}
			else
			{
				myBrokenArgs[++i] = strtok(NULL, " ");
			}
		}
/*************************************************************************************************/
		if(needsPipe == 1) // if piping is needed
		{
			int myPipingDescriptors[2];
			if(pipe(myPipingDescriptors) == -1)
			{
				exit(0);
			}
			int id = fork();
			if(id == 0) // child 1-a
			{
				dup2(myPipingDescriptors[1],1);
				close(myPipingDescriptors[0]);
				close(myPipingDescriptors[1]);
				execvp(myBrokenArgs[0], myBrokenArgs);
				exit(0);
			}
			else if(id > 0) // parent process
			{
				if(fork() ==  0) // child 1-b
				{
					dup2(myPipingDescriptors[0],0);
					close(myPipingDescriptors[0]);
					close(myPipingDescriptors[1]);
					if(needsRedirect == 1 || needsRedirect == 2)
					{
						int pid = fork(); 
						if(pid == 0) // child 2-b
						{
							if(needsRedirect == 1)
							{
								int myDescriptor = open(myFileName, O_CREAT | O_RDWR | O_TRUNC, 0644);
								dup2(myDescriptor, 1); // STDOUT		  
								close(myDescriptor);
							}
							else if(needsRedirect == 2)
							{
								int myDescriptor = open(myFileName, O_CREAT | O_RDWR | O_TRUNC, 0644);
								dup2(myDescriptor, 2); // STDIN				  
								close(myDescriptor);
							}
						}
						else
						{
							wait(0);
						}
					}
					execvp(myBrokenArgs2[0], myBrokenArgs2);
				}
				else
				{
					close(myPipingDescriptors[0]);
					close(myPipingDescriptors[1]);
					wait(0);
					wait(0);
				}
			}
		}
/*************************************************************************************************/
		if(needsPipe == 0) // if piping is not needed
		{
			int pid = fork(); 
			if(pid == 0) // make child process
			{
				if(needsRedirect == 1)
				{
					int myDescriptor = open(myFileName, O_CREAT | O_RDWR | O_TRUNC, 0644);
					dup2(myDescriptor, 1); // STDOUT
					close(myDescriptor);
				}
				else if(needsRedirect == 2)
				{
					int myDescriptor = open(myFileName, O_CREAT | O_RDWR | O_TRUNC, 0644);
					dup2(myDescriptor, 2); // STDIN
					close(myDescriptor);
				}
				execvp(myBrokenArgs[0], myBrokenArgs);
			}
			else
			{
				wait(0);
			}
		}
/*************************************************************************************************/
	}
	return 0;
}

