#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

extern char **getln();
int numphil = 0;
int numeat = 0;
int chopsticks[10000];
int philname[10000];
int nummeals[10000];
pthread_mutex_t chop[10000];
int activity[10000];

//function to determine whether the philosoper is eating or not
void *eatfunction(void  *arg) 
{   
	//takes the restriction from the function call
	int philosopher = *(int*)arg;
	
	//loop as long as the philosopher has eaten less times that specified
	while(nummeals[philosopher-1] < numeat) 
	{ 
		//if the philosopher was not previously thinking, say that it is now thinking
		if(activity[philosopher-1] == 0)
		{
			printf("philosopher %d is thinking!\n", philosopher);
			activity[philosopher-1] = 1;
		} 
 
		// lock the left chopstick  
		pthread_mutex_lock(chop + (philosopher - 1) ); 
		 
		// if the left chopstick is available 
		if(chopsticks[philosopher - 1] == 1) 
		{  
			//philosopher will pick it up and set it as unavailable
			chopsticks[philosopher - 1] = 0;  
			
			//unlock the left chopstick
			pthread_mutex_unlock(chop + philosopher - 1);  
 
			//lock the right chopstick  
			pthread_mutex_lock(chop + (philosopher % numphil)); 
			
			//if the right chopstick is available 
			if(chopsticks[philosopher % numphil] == 1)  
			{ 
				//picks up the chopstick and sets it as unavailable 
				chopsticks[philosopher % numphil] = 0; 
				 
				// unlock the right chopstick  
				pthread_mutex_unlock(chop + (philosopher % numphil)); 
		  
				//philosopher has both chopsticks so it will now eat
				printf("philosopher %d is eating!\n", philosopher); 
				//sets the activity to eating
				activity[philosopher - 1] = 0;
		
				//increments the number of meals the philosopher has eaten
				nummeals[philosopher - 1]++;
				//time the philosopher spends eating
				usleep(rand() % 500000); 
 
				// when done eating locks the left and right chopsticks
				pthread_mutex_lock(chop + philosopher - 1);  
				pthread_mutex_lock(chop + (philosopher % numphil));
				 
				//sets the left chopstick as available
				chopsticks[philosopher - 1] = 1;    
				
				//set the right chopstick as available
				chopsticks[philosopher % numphil] = 1;  
 
				//unlocks the left and right chopsticks
				pthread_mutex_unlock(&chop[philosopher - 1]); 
				pthread_mutex_unlock(&chop[philosopher % numphil]); 
				
				//time the philosopher will wait before eating again
				usleep(rand() % 60000000); 
			} 
			//if the right chopstick is unavailable
			else
			{ 
				//unlock the right chopstick
				pthread_mutex_unlock(&chop[philosopher % numphil]); 
 
				//lock the left chopstick 
				pthread_mutex_lock(&chop[philosopher - 1]); 
				 
				//puts down the left chopstick 
				chopsticks[philosopher - 1] = 1; 
 
				//unlock the left chopstick 
				pthread_mutex_unlock(&chop[philosopher - 1]); 

				//time the philosopher will wait before trying again
				usleep(rand() % 3000000); 
			} 
		}   
		//if the left chopstick is unavailable
		else 
		{ 
			//unlock the left chopstick 
			pthread_mutex_unlock(&chop[philosopher - 1]); 
			 
		   //time the philosopher will wait before trying again
			usleep(rand() % 3000000);
		} 
	
		//changes thread
		sched_yield();
	}  
	//terminates the thread
	pthread_exit(0); 
}	

int main() {
	char **args; 
	int i = 0;
	pthread_t name[10000];
	void *status;
	
	while(1) 
	{
		printf("->");
		args = getln();

		while(args[i] != NULL)
		{
			i++;
		}

		//if user enters "exit", will terminate the program
		if(strcmp(args[0], "exit") == 0)
		{
			_exit(0);
		}
		//if user enters "dine # #", will do dining philosophers algorithm
		else if(i == 3 && !strcmp(args[0], "dine"))
		{
			//takes in user enteres number of philosophers and number of times they must eat
			numphil = atoi(args[1]);
			numeat = atoi(args[2]);
		}
		//if not the two above will do nothing
		else
		{
			printf("Not a valid command please try again\n");
			_exit(0);
		}
		
		for(i = 0; i < numphil; i++)
		{
			//sets all chopsticks to 1
			chopsticks[i] = 1;
			//sets intial amount of meals eaten to 0
			nummeals[i] = 0;
			//sets the philosopher number
			philname[i] = i+1;
			//sets the initial activity 
			activity[i] = 0;
		}
		
		//creates threads for each philosopher
		for (i = 0; i < numphil; i++) 
		{ 
			//if the thread is not created terminates the algorithm
			if(pthread_create(name + i, 0, eatfunction, philname + i) != 0) 
			{ 
				perror("Failed to create thread"); 
				_exit(0);
			} 
		} 
 
		//wait for the join of the philosopher threads 
		for (i = 0; i < numphil; i++) 
		{ 
			//if thread does not join terminates the program
			if(!pthread_join(name[i], &status )==0) 
			{ 
				perror("failed to join thread"); 
				_exit(0); 
			} 
		}
		printf("\n\n");
		//prints out the total time each philosopher eats
		for (i = 0; i < numphil; i++) 
		{ 
			printf("Philosopher %d has eaten %d times\n", philname[i], nummeals[i]);
		}  		
	}
	
return 0;	
}
