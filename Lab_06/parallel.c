// ****************************************
// Program Title: Lab 06
// Project File: parallel.c
// Name: David Thornton
// Course Section: CPE-435, SP 2021
// Due Date: 02/22/2021
// ****************************************
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#define LENGTH 1

double sum, dx;
unsigned long num_threads, num_rectangles;
pthread_mutex_t myMutex;

double f(double inval); // f(x)
void* updateSum(void* argument);

int main(int argc, char* argv[])
{
	clock_t t = clock();
	if(argc != 3)
	{
		printf("ERROR!!! Wrong amount of input arguments. Try again.\nTerminating program...\n");
		return 1;
	}
	sum = 0;
	num_rectangles = atoi(argv[1]);
	num_threads = atoi(argv[2]);
	printf("Number of rectangles = %ld\n", num_rectangles);
	printf("Number of threads    = %ld\n", num_threads);
	dx = LENGTH / (double)num_rectangles; // width of 1 rectangle
	pthread_t myThreads[num_threads];
	int start[num_threads];

	if(num_rectangles < 0)
	{
		printf("ERROR!!! Input can not be negative. Try again.\nTerminating program...\n");
		return 2;
	}

	if(pthread_mutex_init(&myMutex, NULL))
	{
		printf("ERROR!!! Cannot init mutex lock. Try again.\nTerminating program...\n");
		return 3;
	}

    for(int i = 0; i < num_threads; i++)
	{
		start[i] = i; // tell each of the threads where to start
		if(pthread_create(&myThreads[i], NULL, updateSum, &start[i]))
		{
			printf("ERROR!!! Could not create the threads.\nTerminating program...\n");
			return 4;
		}
	}
	
	for(int i = 0; i < num_threads; i++)
	{
		int retStatus = pthread_join(myThreads[i], NULL);
		if(retStatus)
		{
			printf("ERROR!!! Problem at thread id %d.\nError number:%d\n", i, retStatus);
		}
	}

    pthread_mutex_destroy(&myMutex);
    sum *= 4;
	printf("Sum    = %1.9g\n", sum);
    printf("Actual = %1.9g\n", M_PI);
    double error = (1 - M_PI / sum);
    printf("Error  = %.1e\n", error);
    t = clock() - t;
    double total_time = ((double)t)/CLOCKS_PER_SEC;
    double ms = total_time * 1000;
    if(ms < 1000)
    {
   		printf("Program took %g milliseconds to execute\n", ms);
    }
    else if(ms >= 1000)
    {
    	printf("Program took %g seconds to execute\n", total_time);
	}
    return 0;
}

double f(double inval)
{
	return(sqrt(1 - pow(inval, 2)));
}

void* updateSum(void* arg)
{
	double x, temp;
	int myStart = *(int*) arg;
	temp = 0; // make sure the sum is 0 for each thread call
	for (unsigned long i = myStart; i < num_rectangles; i += num_threads)
	{
		x = dx * i;
		temp += dx * f(x);
	}
	pthread_mutex_lock(&myMutex);
	sum += temp;
	pthread_mutex_unlock(&myMutex);
	return(NULL);
}

// Compile with: gcc parallel.c -o runner_parallel -Wall -lm -pthread
