#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <math.h>

extern char **getln();

void sig_handler(int signal) {
  int status;
  int result = wait(&status);

  printf("Wait returned %d\n", result);
}

int main() {
	int i = 0;
	int j = 0;
	int k = 0;
	int argc = 0;
	int amp = 0;
	int output = 0;
	int input = 0;
	int add = 0;
	int temp = 0;
	char **args; 
	char filename[100];
	pid_t child;
	int status;
	
	signal(SIGCHLD, sig_handler);
	
	while(1) 
	{
		printf("->");
		args = getln();

		while(args[i] != NULL)
		{
			i++;
		}

		if(strcmp(args[0], "exit") == 0)
		{
			_exit(0);
		}
		if(i > 2 && !strcmp(args[i-2], ">"))
		{
			if(args[i-1] != NULL)
			{
				strcpy(filename, args[i-1]);
				free(args[i-1]);
				for(j = (i-2); args[j-1] != NULL; j++) 
				{
					args[j] = args[j+2];
				}
				printf("Redirecting output to: %s\n", filename);
				output = 1;
			}
			else
			{
				printf("Syntax Error\n");
			}
		}
		if(i > 2 && !strcmp(args[i-2], "<"))
		{
			if(args[i-1] != NULL)
			{
				strcpy(filename, args[i-1]);
				free(args[i-1]);
				for(j = (i-2); args[j-1] != NULL; j++) 
				{
					args[j] = args[j+2];
				}
				printf("Redirecting input to: %s\n", filename);
				input = 1;
			}
			else
			{
				printf("Syntax Error\n");
			}
		}
		if(!strcmp(args[i-1], "&"))
		{
			amp = 1;
			free(args[i-1]);
			args[i-1] = NULL;
		}
		if(!strcmp(args[0], "add"))
		{
			add = 0;
			for(j = 1; j < i; j++)
			{
				if(strstr(args[j], "0x"))
				{
					temp = strtol(args[j], NULL, 0);
					add = add + temp;
				}
				else
				{
					add = add + atoi(args[j]);
				}
				if(j != i-1)
				{
					printf("%s + ", args[j]);
				}
				else
				{
					printf("%s", args[j]);
				}
			}
			printf(" = %d\n", add);
		}
		if(!strcmp(args[0], "arg"))
		{
			printf("args = ");
			for(j = 1; j < i; j++)
			{
				if(strstr(args[j],"1") || strstr(args[j],"2") || strstr(args[j],"3") || strstr(args[j],"4") || strstr(args[j],"5") || strstr(args[j],"6") || strstr(args[j],"7") || strstr(args[j],"8") || strstr(args[j],"9") || strstr(args[j],"0"))
				{
					argc++;
					if(k==0)
					{
						printf("%s, ", args[j]);
						k = 0;
					}
					else
					{
						printf("'', %s, ", args[j]);
						k = 0;
					}
				}
				else
				{
					if(k == 0)
					{
						printf("''%s", args[j]);
						k++;
						argc++;
					}
					else
					{
						printf(", %s", args[j]);
					}
				}
			}
			if(k > 0)
			{
				printf("'' argc = %d\n", argc);
			}
		}
		if(!strcmp(args[0], "mult"))
		{
			add = 0;
			for(j = 1; j < i; j++)
			{
				if(strstr(args[j], "0x"))
				{
					temp = strtol(args[j], NULL, 0);
					add = add * temp;
				}
				else
				{
					add = add * atoi(args[j]);
				}
				if(j != i-1)
				{
					printf("%s * ", args[j]);
				}
				else
				{
					printf("%s", args[j]);
				}
			}
			printf(" = %d\n", add);
		}
		
		child = fork();

		switch(child) 
		{
			case EAGAIN:
				perror("Error EAGAIN: ");
				break;
			case ENOMEM:
				perror("Error ENOMEM: ");
				break;
		}

		if(child == 0) 
		{
			if(input == 1)
			{
				freopen(filename, "r", stdin);
			}
			else if(output == 1)
			{
				freopen(filename, "w+", stdout);
			}

			// Execute the command
			execvp(args[0], args);

			_exit(-1);
		}

		// Wait for the child process to complete, if necessary
		if(amp == 1) 
		{
			printf("Waiting for child, pid = %d\n", child);
			waitpid(child, &status, 0);
			
		}
		
		for(j = 0; j < i; j++)
		{
			free(args[j]);
		}
	}
}
