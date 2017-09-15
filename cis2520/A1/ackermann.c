#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*funtion to calculate ackermann value*/
int function(int n, int m)
{
	if (n == 0)
	{
		return m + 1;
	}
	if (m == 0)
	{
		return function(n - 1, 1);
	}
return function(n - 1, function(n, m - 1));
}

int ackermann(void)
{
	int n = 0; /*int to store user inputs*/
	int m = 0;
	
	printf("Please enter the n and m values seperated by a space\n");
	scanf("%d %d", &n, &m); /*scans in user input*/
	printf("A(%d, %d) = %d\n", n, m, function(n,m));/*prints out the ackermann value*/
	
return 0;
}
	

		
		
	
