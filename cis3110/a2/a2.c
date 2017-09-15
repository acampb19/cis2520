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

int main() {
	FILE * fp;
	int time = 0, i = 0, j = 0, k = 0, m = 0, next = 0, counter = 0, num = 0;
	int dynamic = 0, rr = 0, quantum = 0, numprocesses = 0, process = 0;
	char **args; 
	char filename[100];
	char * array[300];
	char * token;
	int threadswitch = 0, processswitch = 0;
	int numcpu[10][10]; // holds number of cpu's in a thread
	int arrival[10][50]; //process, thread
	int cputime [10][10][50]; // process, thread, cpu
	int remtime [10][10][50];
	int iotime [10][10][50]; // process, thread, cpu
	int totaltime[10][10];
	int nextthread = 0, cpu = 0, numthreads[10], thread = 0, previ = -1;
	int kspot[10][10];
	int turnaround[10][10];
	int averageturn = 0;
	int maxtime = 0;
	double a[4], b[4];
	double loadavg;
	int orderedarrival[500];
	int orderedprocess[100];
	int orderedthread[500];
	
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
		if(i > 1 && !strcmp(args[0], "simcpu"))
		{
			
			if(args[i-1] != NULL)
			{
				strcpy(filename, args[i-1]);
				if(i > 5)
				{
					rr = 1;
					quantum = atoi(args[3]);
					if(!strcmp(args[1], "-d"))
					{
						dynamic = 1;
						printf("Round Robin (quantum = %d time units)\n", quantum);
					}
				}
			}
			else
			{
				printf("Syntax Error\n");
			}
		}
		
		fp = fopen(filename, "r");
		
		if(fp == NULL)
		{
			printf("Error opening file\n");
		}
		
		array[num] = (char*)malloc(sizeof(char*));
		while(fgets(array[num], 300, fp)!= NULL)
		{
			num++;
			array[num] = (char*)malloc(sizeof(char*));
		}
		fclose(fp);
	
		for(j = 0; j < num; j++)
		{
			token = strtok(array[j], " ");
			while(token != NULL)
			{
				if(counter == 0 && j == 0)
				{
					numprocesses = atoi(token);
				}
				else if(counter == 1 && j == 0)
				{
					threadswitch = atoi(token);
				}
				else if(counter == 2 && j == 0)
				{
					processswitch = atoi(token);
				}
				else if(counter == 0 && j == 1)
				{
					process = atoi(token);
				}
				else if(counter == 1 && j == 1)
				{
					numthreads[process] = atoi(token);
				}
				else if(counter == 0 && j == 2)
				{
					thread = atoi(token);
				}
				else if(counter == 1 && j == 2)
				{
					arrival[process][thread] = atoi(token);
				}
				else if(counter == 2 && j == 2)
				{
					numcpu[process][thread] = atoi(token);
					nextthread = j + numcpu[process][thread] + 1;
				}
				else if(counter == 0 && next == 1 && thread == numthreads[process] && j == nextthread)
				{
					process = atoi(token);
				}
				else if(counter == 1  && next == 1  && numthreads[process] == 0 && j == nextthread)
				{
					thread = 0;
					numthreads[process] = atoi(token);
					nextthread++;
					next = 0;
				}
				else if(counter == 0 && j == nextthread && thread < numthreads[process])
				{
					thread = atoi(token);
				}
				else if(counter == 1 && j == nextthread)
				{
					arrival[process][thread] = atoi(token);
				}
				else if(counter == 2 && j == nextthread)
				{
					numcpu[process][thread] = atoi(token);
					nextthread = j + numcpu[process][thread] + 1;
					if(thread == numthreads[process])
					{
						next = 1;
					}
				}
				else if(counter == 0 && j < nextthread)
				{
					cpu = atoi(token);
				}
				else if(counter == 1 && j < nextthread)
				{
					cputime[process][thread][cpu] = atoi(token);
					remtime[process][thread][cpu] = atoi(token);
				}
				else if(counter == 2 && j < nextthread)
				{
					iotime[process][thread][cpu] = atoi(token);
				}
				counter++;
				token = strtok(NULL, " ");
			}
			counter = 0;
		}
		
		int countthing = 0;
		for(i = 1; i <= numprocesses; i++)
		{
			for(j = 1; j <= numthreads[i]; j++)
			{
				
				if(countthing == 0)
				{
					orderedarrival[0] = arrival[i][j];
					orderedprocess[0] = i;
					orderedthread[0] = j;
				}
				else
				{
					if(arrival[i][j] > orderedarrival[countthing-1] || arrival[i][j] == orderedarrival[countthing-1])
					{
						orderedarrival[countthing] = arrival[i][j];
						orderedprocess[countthing] = i;
						orderedthread[countthing] = j;
					}
					else
					{
						for(k = 0; k < countthing; k++)
						{
							if(arrival[i][j] > orderedarrival[k-1] && arrival[i][j] < orderedarrival[k])
							{
								for(m = (countthing-1); m >= k; m--)
								{
									orderedarrival[m + 1] = orderedarrival[m];
									
									orderedprocess[m + 1] = orderedprocess[m];
									orderedthread[m + 1] = orderedthread[m];
								}
								
								orderedarrival[k] = arrival[i][j];
								orderedprocess[k] = i;
								orderedthread[k] = j;
								break;
							}
							else if(arrival[i][j] == orderedarrival[k])
							{
								for(m = (countthing-1); m >= (k+1); m--)
								{
									orderedarrival[m + 1] = orderedarrival[m];
									
									orderedprocess[m + 1] = orderedprocess[m];
									orderedthread[m + 1] = orderedthread[m];
								}
								
								orderedarrival[k+1] = arrival[i][j];
								orderedprocess[k+1] = i;
								orderedthread[k+1] = j;
								break;
							}
						}
					}
				}
				countthing++;
			}
		}
		
		int value = 0, flag = 0, newthread[10][10], servicetime[10][10], donethread[10];

		for(i = 1; i <= numprocesses; i++)
		{
			donethread[i] = 0;
			for(j = 1; j <= numthreads[i]; j++)
			{
				kspot[i][j] = 1;
				newthread[i][j] = 1;
			} 
		}
		i = 0; // process number
		k = 1;
		
		fp = fopen("/proc/stat", "r");
		fscanf(fp, "%*s %lf %lf %lf %lf", &a[0], &a[1], &a[2], &a[3]);
		fclose(fp);
		sleep(1);
		
		while(value < numprocesses && rr == 0)
		{
			if(i == 0)
			{
				time = time + threadswitch;
			}
			j = orderedthread[i];
			m = orderedprocess[i];
			
			time = time + remtime[m][j][k];
			
			if(k < numcpu[m][j])
			{
				k++;
			}
			else if(k == numcpu[m][j] && j < numthreads[m])
			{
				totaltime[m][j] = time + iotime[m][j][k];
				if(maxtime < totaltime[m][j])
				{
					maxtime = totaltime[m][j];
				}
				turnaround[m][j] = totaltime[m][j] - arrival[m][j];
				k = 1;
				i++;
			}
			else if(k == numcpu[m][j] && j == numthreads[m])
			{
				totaltime[m][j] = time + iotime[m][j][k];
				if(maxtime < totaltime[m][j])
				{
					maxtime = totaltime[m][j];
				}
				turnaround[m][j] = totaltime[m][j] - arrival[m][j];
				k = 1;
				value++;
				i++;
			}
			
			if(value != numprocesses && orderedprocess[i] != orderedprocess[i-1])
			{
				time = time + processswitch;
			}
			else if(value != numprocesses)
			{
				time = time + threadswitch;
			}
		}

		while(value < numprocesses && rr == 1)
		{
			j = orderedthread[i]; // thread
			m = orderedprocess[i]; //process
			k = kspot[m][j]; //cpu location
			
			if(previ > -1)
			{
				if(m == orderedprocess[previ] && newthread[m][j] == 1)
				{
					servicetime[m][j] = servicetime[m][j] + threadswitch;
					time = time + threadswitch;
					newthread[m][j] = 0;
					if(dynamic == 0)
					{
						printf("At time %d thread %d of process %d went from new to ready\n\n", time, j, m);
					}
				}
				else if(m != orderedprocess[previ] && newthread[m][j] == 1)
				{
					servicetime[m][j] = servicetime[m][j] + processswitch;
					time = time + processswitch;
					newthread[m][j] = 0;
					if(dynamic == 0)
					{
						printf("At time %d thread %d of process %d went from new to ready\n", time, j, m);
					}
				}
			}
			else
			{
				if(newthread[m][j] == 1)
				{
					servicetime[m][j] = servicetime[m][j] + threadswitch;
					time = time + threadswitch;
					newthread[m][j] = 0;
				}
				if(dynamic == 0)
				{
					printf("At time %d thread %d of process %d went from new to ready\n\n", time, j, m);
				}
			}
			
			if(remtime[m][j][k] <= quantum && remtime[m][j][k] > 0)
			{
				if(dynamic == 0)
				{
					printf("At time %d thread %d of process %d went from ready to running\n\n", time, j, m);
				}
				time = time + remtime[m][j][k];
				remtime[m][j][k] = 0;
				flag = 1;
			}
			else if(remtime[m][j][k] > 0)
			{
				if(dynamic == 0)
				{
					printf("At time %d thread %d of process %d went from ready to running\n\n", time, j, m);
				}
				remtime[m][j][k] = remtime[m][j][k] - quantum;
				time = time + quantum;
				if(dynamic == 0)
				{
					printf("At time %d thread %d of process %d went from running to blocked\n\n", time, j, m);
				}
			}
			
			if(remtime[m][j][k] == 0 && flag == 1)
			{
				totaltime[m][j] = totaltime[m][j] + iotime[m][j][k];
				
				if(k < numcpu[m][j])
				{
					kspot[m][j] = kspot[m][j] + 1;
					if(dynamic == 0)
					{
						printf("At time %d thread %d of process %d went from running to blocked\n\n", time, j, m);
					}
				}
				else if(k == numcpu[m][j] && donethread[m] < (numthreads[m]-1))
				{
					totaltime[m][j] = totaltime[m][j] + time;
					if(maxtime < totaltime[m][j])
					{
						maxtime = totaltime[m][j];
					}
					turnaround[m][j] = totaltime[m][j] - arrival[m][j];
					kspot[m][j] = 1;
					donethread[m]++;
					if(dynamic == 0)
					{
						printf("At time %d thread %d of process %d went from running to terminated\n\n", time, j, m);
					}
				}
				else if(k == numcpu[m][j] && donethread[m] == (numthreads[m]-1))
				{
					totaltime[m][j] = totaltime[m][j] + time;
					if(maxtime < totaltime[m][j])
					{
						maxtime = totaltime[m][j];
					}
					turnaround[m][j] = totaltime[m][j] - arrival[m][j];
					kspot[m][j] = 1;
					value++;
					if(dynamic == 0)
					{
						printf("At time %d thread %d of process %d went from running to terminated\n\n", time, j, m);
					}
				}
				flag = 0;
				
			}
			previ = i;
			if(i == (countthing - 1))
			{
				i = 0;
			}
			else if(arrival[orderedprocess[i+1]][orderedthread[i+1]] <= time)
			{
				i++;
			}
			else
			{
				i = 0;
			}
		}
		
		fp = fopen("/proc/stat", "r");
		fscanf(fp, "%*s %lf %lf %lf %lf", &b[0], &b[1], &b[2], &b[3]);
		fclose(fp);
		
		double percent = 0;
		loadavg = loadavg + (b[0] - a[0]);
		loadavg = loadavg + (b[1] - a[1]);
		loadavg = loadavg + (b[2] - a[2]);
		percent = loadavg;
		loadavg = loadavg + (b[3] - a[3]);
		percent = percent/loadavg;
		percent = percent * 100;
		
		int totalio = 0;
		if(rr == 0)
		{
			printf("Total time required is %d units\n", maxtime);
			for(i = 1; i <=numprocesses; i++)
			{
				for(j = 1; j <=numthreads[i]; j++)
				{
					thread++;
					averageturn = averageturn + turnaround[i][j];
				}
			}
			printf("Average Turn around time is %d units\n", (averageturn/thread));
			printf("CPU utilization is %.2lf percent\n\n", percent);
		}
		
		if(dynamic == 1)
		{
			printf("Total time required is %d units\n", maxtime);
			for(i = 1; i <=numprocesses; i++)
			{
				for(j = 1; j <=numthreads[i]; j++)
				{
					thread++;
					averageturn = averageturn + turnaround[i][j];
				}
			}
			printf("Average Turn around time is %d units\n", (averageturn/thread));
			printf("CPU utilization is %.2lf percent\n\n", percent);
			
			for(i = 1; i <= numprocesses; i++)
			{
				for(j = 1; j <= numthreads[i]; j++)
				{
					totalio = 0;
					printf("Thread %d of Process %d: \n\n", j, i);
					printf("arrival time: %d units\n", arrival[i][j]);
					printf("Service time: %d units\n", servicetime[i][j]);
					
					for(k = 1; k < numcpu[i][j];k++)
					{
						totalio = totalio + iotime[i][j][k];
					}
					
					printf("I/O time: %d units\n", totalio);
					printf("Turn around time: %d units\n", turnaround[i][j]);
					printf("Finish time: %d units\n\n", totaltime[i][j]);
				}
			}
		}
						
	}
	
return 0;	
}
