#include "carbon.c"
#include "ackermann.c"
#include "newton.c"


int main(void)
{
	int choice = 0; /*int for user choice*/
	/*if user choice is 5, quit program*/
	while(choice != 5)
	{
		/*takes user choice for what code to implement*/
		printf("\nWhat action would you like to perfom?\n1. Print all permutations of CARBON\n2. Perform Ackermann Function\n");
		printf("3. Find square using Newton's method\n4. Find square using Newton's method recursively\n5. Quit\n");
		scanf("%d", &choice);/*scans in choice and stores to choice*/
	
		if(choice == 1)
		{
			/*if 1 implement carbon.c*/
			carbon();
		}
		else if(choice == 2)
		{
			/*if 2 implement ackermann.c*/
			ackermann();
		}
		else if(choice == 3)
		{
			/*if 3 implement newton.c*/
			newton();
		}
		else if(choice == 4)
		{
			/*if 4 implement newton2.c (recursive newton)*/
			newton2();
		}
	}
return 0;
}
