#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*function to calculate square by newton method*/
void newton(void)
{
	/*declared doubles for input number, accuracy, approximate square and step*/
	time_t start, finish; /*variables for start time and finish time*/
	double totaltime;
	double number = 0;
	double accuracy = 0;
	double approx = 0;
	double step = 0;
	
	printf("Please enter the number you wish to calculate the square root of\n");
	scanf("%lf", &number); /*scans in number to take square of*/
	printf("Please enter the accuracy\n");
	scanf("%lf", &accuracy);
	
	step = accuracy + 1;
	
	/*if number is not positive and real allow re-entry*/
	while(number <= 0)
	{
		printf("Please enter a positive real number\n");
		scanf("%lf", &number);
	}
	
	start = time(NULL);/*get start time*/
	/*first approximation*/
	approx = number/2;
	
	/*while not within the accuracy range continue looping*/
	while(step > accuracy)
	{
		step = (approx * approx) - number;
	
		if(step < 0)
		{
			step = step *-1;
		}
		/* if accurate enough print the number*/
		if(step <= accuracy)
		{
			printf("The square root of %.2f is %.2f\n", number, approx);
		}
		else
		{
			/*if not accurate enough get a new approximation*/
			approx = (approx + (number/approx))/2;
		}
	}
	finish = time(NULL);/*get finish time*/
	totaltime = difftime(finish, start); /*calculate difference in time*/
	printf("total time taken is %f seconds\n", totaltime);/*print out total time*/
}

/*function to find the square by newtons method recursively*/
void recursive(double number, double approx, double accuracy)
{
	/*double for step*/
	double step = 0;
	
	step = (approx * approx) - number;
	
	if(step < 0)
	{
		step = step *-1;
	}
	/*if accurate enough print the number*/
	if(step <= accuracy)
	{
		printf("The square root of %.2f is %.2f\n", number, approx);
	}
	else
	{
		/*if not accurate enough get new approximation*/
		approx = (approx + (number/approx))/2;
		/*send new approximation back into function*/
		recursive(number, approx, accuracy);
	}
}

void newton2(void)
{
	time_t start, finish; /*variables for start time and finish time*/
	double totaltime;
	double number = 0;
	double approx = 0;
	double accuracy = 0;
	
	/*take user input of number to be squared*/
	printf("Please enter the number you wish to calculate the square root of\n");
	scanf("%lf", &number);
	printf("Please enter the accuracy\n");
	scanf("%lf", &accuracy);
	
	/*if number is not positive and real allow re-entry*/
	while(number <= 0)
	{
		printf("Please enter a positive real number\n");
		scanf("%lf", &number);
	}
	
	start = time(NULL);
	/*first approximation*/
	approx = number/2;
	/*send number and square into function*/
	recursive(number, approx, accuracy);
	
	finish = time(NULL);/*get finish time*/
	totaltime = difftime(finish, start); /*calculate difference in time*/
	printf("total time taken is %f seconds\n", totaltime);/*print out total time*/
}
