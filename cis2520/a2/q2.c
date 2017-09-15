#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int add(char*token, double* array, int i)
{
	double total = 0;
	int num1 = 0;
	int num2 = 0;
	double number1;
	double number2;
	
	num1 = atoi(token);
	if(num1 == 0)
	{
		total = array[i-1] + array[i-2];
	}
	else
	{			
		num2 = num1 % 10;
		number2 = (double) num2;
		num1 = num1 / 10;
		if(num1 == 0)
		{
			num1 = array[i-1];
		}
		number1 = (double) num1;
		total = number1 + number2;
	}
	
	array[i] = total;
return total;
}

int subtract(char*token, double*array, int i)
{
	int num1 = 0;
	int num2 = 0;
	double number1;
	double number2;
	double total = 0;
	
	num1 = atoi(token);
	if(num1 == 0)
	{
		total = array[i-2] - array[i-1];
	}
	else
	{
		num2 = num1 % 10;
		number2 = (double) num2;
		num1 = num1 / 10;
		if(num1 == 0)
		{
			num1 = array[i-1];
		}
		number1 = (double) num1;
		total = number1-number2;
	}
	array[i] = total;
return total;
}

int multiply(char*token, double*array, int i)
{
	int num1 = 0;
	int num2 = 0;
	double number1;
	double number2;
	double total = 0;
	
	num1 = atoi(token);
	if(num1 == 0)
	{
		total = array[i-2] * array[i-1];
	}
	else
	{
		num2 = num1 % 10;
		number2 = (double) num2;
		num1 = num1 / 10;
		if(num1 == 0)
		{
			num1 = array[i-1];
		}
		number1 = (double) num1;
		total = number1*number2;
	}
	array[i] = total;
return total;
}

int divide(char*token, double*array, int i)
{
	int num1 = 0;
	int num2 = 0;
	double number1;
	double number2;
	double total = 0;
	
	num1 = atoi(token);
	if(num1 == 0)
	{
		total = array[i-2] / array[i-1];
	}
	else
	{
		num2 = num1 % 10;
		number2 = (double) num2;
		num1 = num1 / 10;
		if(num1 == 0)
		{
			num1 = array[i-1];
		}
		number1 = (double) num1;
		total = number1/number2;
	}
	array[i] = total;
return total;
}

int main(int argc, char *argv[])
{
	char input[100];
	char *token;
	double array[100];
	int a;
	int i = 0;
	int j = 0;
	strcpy(input, argv[1]);
	for(a=0; a < 6; a++)
	{
		if(argc != 2)
		{
			printf("You did not enter a postfix expression to be evaluated\n");
			return 0;
		}
		if(j == 0)
		{
			if(input[a] == '+')
			{
				token = strtok(input, "+");
				add(token, array, i);
				j++;
				i++;
			}
			else if(input[a] == '-')
			{
				token = strtok(input, "-");
				subtract(token, array, i);
				j++;
				i++;
			}
			else if(input[a] == '*')
			{
				token = strtok(input, "*");
				multiply(token, array, i);
				j++;
				i++;
			}
			else if(input[a] == '/')
			{
				token = strtok(input, "/");
				divide(token, array, i);
				j++;
				i++;
			}
		}
		else
		{
			if(input[a] == '+')
			{
				token = strtok(NULL, "+");
				add(token, array, i);
				i++;
			}
			else if(input[a] == '-')
			{
				token = strtok(NULL, "-");
				subtract(token, array, i);
				i++;
			}
			else if(input[a] == '*')
			{
				token = strtok(NULL, "*");
				multiply(token, array, i);
				i++;
			}
			else if(input[a] == '/')
			{
				token = strtok(NULL, "/");
				divide(token, array, i);
				i++;
			}
		}
	}
	
	if(input[6] == '+')
	{
		array[i] = array[i-2] + array[i - 1];
		i++;
	}
	if(input[6] == '-')
	{
		array[i] = array[i-2] - array[i - 1];
		i++;
	}	
	if(input[6] == '*')
	{
		array[i] = array[i-2] * array[i - 1];
		i++;
	}	
	if(input[6] == '/')
	{
		array[i] = array[i-2] / array[i - 1];
		i++;
	}
	printf("The answer to the post fix expression is %.2f\n", array[i-1]);
	return 0;
}
