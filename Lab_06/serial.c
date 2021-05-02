// ****************************************
// Program Title: Lab 06
// Project File: serial.c
// Name: David Thornton
// Course Section: CPE-435, SP 2021
// Due Date: 02/22/2021
// ****************************************
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#define UPPER 1
#define LOWER 0

double getWidth(double upper, double lower, int num);
double getHeight(double width, int i);

int main(int argc, char* argv[])
{
	clock_t t = clock();
	if(argc != 2)
	{
		printf("ERROR!!! Wrong amount of input arguments. Try again.\nTerminating program...\n");
		return 1;
	}
	
	unsigned long num_rectangles = atoi(argv[1]);
	
	if(num_rectangles < 0)
	{
		printf("ERROR!!! Input can not be negative. Try again.\nTerminating program...\n");
		return -1;
	}
	
	double sum = 0;
    double width = getWidth(UPPER, LOWER, num_rectangles);
    
    for(int i = 0; i < num_rectangles; i++)
    {
        sum += width * getHeight(width, i);
    }
    
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

double getWidth(double upper, double lower, int num)
{
    double width = ((upper - lower) / num);
    return width;
}

double getHeight(double width, int i)
{
	double x = width * i;
    double height = sqrt(1 - pow(x, 2));
    return height;
}

// gcc serial.c -o runner_serial -Wall -lm
