#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <math.h>

int timesremoved[100]; //array that holds the number of times the process has been removed from memory
char name[100]; //array of the process names
int num;
extern char **getln(); //gets user input

//linked list for the memory
struct mem{
	char name; //name of block
	int size; //size of the block
	int type; //0 for hole 1 for data
	int time; //when put into the list
	struct mem * next;
}*memory;

//linked list for the queue
struct node{
	char name; //name of process
	int size; //size of process
	struct node * next;
}*queue;

//function to add to the end of the queue
void addend(int num, char process)
{
    struct node *temp,*right; //temp list values
    temp= (struct node *)malloc(sizeof(struct node)); //allocates memory for temp values
    temp->size = num; //adds the size to the list
    temp->name = process; //add the process name to the list
    right = (struct node *)queue;
    //loop to find the end of the list
    while(right->next != NULL)
    {
		right=right->next;
    }
    //appends the new node to the list
    right->next = temp;
    right = temp;
    right->next = NULL;
}

//function to add to the front of the queue
void addfront(int num, char process)
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->name = process;
    temp->size = num;
    if(queue == NULL)
    {
		queue = temp;
		queue->next = NULL;
    }
    else
    {
		temp->next = queue;
		queue = temp;
    }
}

//function to add to the front of the memory
void addfrontmem(int num, char process, int j, int i)
{
    struct mem *temp;
    temp = (struct mem *)malloc(sizeof(struct mem));
    temp->name = process;
    temp->size = num;
    temp->type = j;
    temp->time = i;
    if(memory == NULL)
    {
		memory = temp;
		memory->next = NULL;
    }
    else
    {
		memory->size = memory->size - temp->size;
		if(memory->size == 0)
		{
			memory = temp;
			temp->next = memory->next;
		}
		else
		{
			temp->next = memory;
			memory = temp;
		}
    }
}

//function to add to the middle of the memory
void addafter(struct mem *temp, struct mem *prev, char process, int num, int i, int j)
{
    struct mem *temp2;
    temp2 = (struct mem *)malloc(sizeof(struct mem));
    temp2->name = process;
    temp2->size = num;
    temp2->type = j;
    temp2->time = i;
    temp->size = temp->size - temp2->size;
    if(temp->size == 0)
	{
		temp->size = num;
		temp->name = process;
		temp->type = 1;
		temp->time = i;
    }
    else
    {
		temp2->next = temp;
		prev->next = temp2;
	}
    return;
}
 
//function to insert a node into the queue
void insertq(int num, char process)
{
    struct node *temp;
    temp = queue;
    
    if(temp == NULL)
    {
		addfront(num, process);
    }
    else
    {
		addend(num, process);
	}
}

//function to insert a node into the memory
void insertmem(int num, char process, int j, int i, struct mem *place)
{
    struct mem *temp, *prev;
    temp = memory;
    prev = NULL;
    
    if(place == temp)
    {
		addfrontmem(num, process, j, i);
    }
    else
    {
		while(temp != NULL)
		{
			if(temp != place)
			{
				prev = temp;
				temp = temp->next;
			}
			else
			{
				addafter(temp, prev, process, num, i, j);
				break;
			}
		}
	}
}

//function to delete front process from the  queue once it has been added to the memory
int deleteq(void)
{
    struct node *temp;
    temp = queue;
	queue = temp->next;
	free(temp);
	if(queue == NULL)
	{
		return 0;
	}
return 1;
}
 
//function to delete a block from the memory
int removemem(void)
{
    struct mem *temp, *remove, *prev, *before;
    int earliest = 0;
    int i = 0;
    int remtimes = 0;
    temp = memory;
    prev = NULL;
    while(temp != NULL)
    {
		if(i == 0 && temp->type == 1)
		{
			earliest = temp->time;
			remove = temp;
			before = prev;
			i++;
		}
		else if(temp->type == 1)
		{	
			if(earliest > temp->time)
			{	
				earliest = temp->time;
				remove = temp;
				before = prev;
			}
		}
		
		prev = temp;
		temp = temp->next;
	}
	for(i = 0; i < num; i++)
	{
		if(remove->name == name[i])
		{
			timesremoved[i]++;
			remtimes = timesremoved[i];
			break;
		}
	}
	
	if(before == NULL && remove->next->type == 0)
	{
		if(remtimes != 3)
		{
			insertq(remove->size, remove->name);
		}
		remove->name = 'x';
		remove->type = 0;
		remove->time = 0;
		remove->size = remove->size + remove->next->size;
		remove->next = remove->next->next;
	}
	else if(before == NULL)
	{
		if(remtimes != 3)
		{
			insertq(remove->size, remove->name);
		}
		remove->name = 'x';
		remove->type = 0;
		remove->time = 0;
	}
	else if(remove->next->type == 0 && before->type == 0)
	{
		before->size = before->size + remove->size + remove->next->size;
		before->next = remove->next->next;
		if(remtimes != 3)
		{
			insertq(remove->size, remove->name);
		}
		temp = remove->next;
		free(temp);
		temp = remove;
		free(temp);
	}
	else if(before->type == 0)
	{
		before->size = before->size + remove->size;
		before->next = remove->next;
		if(remtimes != 3)
		{
			insertq(remove->size, remove->name);
		}
		temp = remove;
		free(temp);
	}
	else if(remove->next->type == 0)
	{
		remove->next->size = remove->next->size + remove->size;
		before->next = remove->next;
		if(remtimes != 3)
		{
			insertq(remove->size, remove->name);
		}
		temp = remove;
		free(temp);
	}
	else
	{
		if(remtimes != 3)
		{
			insertq(remove->size, remove->name);
		}
		remove->name = 'x';
		remove->type = 0;
		remove->time = 0;
	}
return 1;
}

//function to count the number of processes in memory
int countprocess()
{
    struct mem *n;
    int p = 0;
    n = memory;
    while(n != NULL)
    {
		if(n->type == 1)
		{
			p++;
		}
		n = n->next;
    }
    return p;
}

//function to count the number of holes in memory
int countholes()
{
    struct mem *n;
    int h = 0;
    n = memory;
    while(n != NULL)
    {
		if(n->type == 0)
		{
			h++;
		}
		n = n->next;
    }
    return h;
}

//function to get the sum of all the processes in memory
double takenspace()
{
    struct mem *n;
    double s = 0;
    n = memory;
    while(n != NULL)
    {
		if(n->type == 1)
		{
			s = s + n->size;
		}
		n = n->next;
    }
    return s;
}

//function to empty the memory
struct mem *empty(struct mem * delete)
{
	struct mem *next, *current;
	current = delete;
	
	while(current != NULL)
	{
		current->type = 0;
		current->size = 0;
		current->time = 0;
		next = current->next;
		free(current);
		current = next;
	}
	delete = NULL;
return current;	
}

void  displaymem(struct mem *r)
{
    r = memory;
    if(r == NULL)
    {
		return;
    }
    while(r != NULL)
    {
		printf("%c %d\n",r->name, r->size);
    r = r->next;
    }
}
void  display(struct node *r)
{
    r = queue;
    if(r == NULL)
    {
		return;
    }
    while(r != NULL)
    {
		printf("%c %d\n",r->name, r->size);
    r = r->next;
    }
} 

int main() {
	FILE * fp;
	int i = 0, j = 1, counth = 0, best = 0, space = 0;
	double taken = 0;
	char **args; 
	char filename[100];
	int size[100];
	char * array[300];
	char * token;
	struct node * root;
	struct mem * first;
	struct node * line;
	struct mem * block;
	memory = NULL;
	queue = NULL;
	double memuse, totproc, tothole, totmem;
	double permem;
	double countp = 0;
	int memsize = 128;
	
	while(1) 
	{
		printf("->");
		args = getln();

		while(args[i] != NULL)
		{
			i++;
		}
		//if user enters "exit" will terminate the program
		if(strcmp(args[0], "exit") == 0)
		{
			_exit(0);
		}
		//if user enters holes will execute memory allocations
		else if(i == 2 && !strcmp(args[0], "holes"))
		{
			strcpy(filename, args[1]);
		}
		else
		{
			printf("Invalid Entry\n");
			_exit(0);
		}
		
		//opens user entered file
		fp = fopen(filename, "r");
		
		//checks if error opening the file
		if(fp == NULL)
		{
			printf("Error opening file\n");
			_exit(0);
		}
		
		//allocated memory for the file read
		array[0] = (char*)malloc(sizeof(char*));
		
		//reads file into an array
		while(fgets(array[num], 300, fp)!= NULL)
		{
			num++;
			array[num] = (char*)malloc(sizeof(char*));
		}
		
		//closes the file
		fclose(fp);
		
		//initializes values and parses file
		for(i = 0; i < num; i++)
		{
			timesremoved[i] = 0;//initilized times loaded to 0
			token = strtok(array[i], " ");
			strcpy(&name[i], token);//takes name of process and stores in name array
			token = strtok(NULL, " ");
			size[i] = atoi(token);//takes size of process and stores it in size array
		}
		
		//adds all processes to the queue
		for(i = 0; i < num; i++)
		{
			insertq(size[i], name[i]);
		}
		
		//initializes the memory to empty
		if(memory == NULL)
		{
			insertmem(128, 'x', 0, 0, memory);
		}
		
		//initializes values
		line = queue;
		block = memory;
		i = 1;
		j = 1;
		
		printf("*--------First Fit--------*\n\n");
		while(line != NULL)
		{
			line = queue;
			if(line->size <= block->size && block->type == 0)
			{
				//if new process fits in an empty block inserts it into memory
				insertmem(line->size, line->name, 1, i, block);
				//calculates the number of processes, holes and memory usage
				countp = countprocess(memory);
				totproc = totproc + countp;
				counth = countholes(memory);
				tothole = tothole + counth;
				taken = takenspace(memory);
				memuse = taken/128.0 * 100;
				totmem = totmem + memuse;
				permem = totmem/i;
				printf("%c loaded, #processes = %.0f, #holes = %d, %%memusage = %.2f, cumulative %%mem = %.2f\n", line->name, countp, counth, memuse, permem);
				j = deleteq();
				if(j == 0)
				{
					//if the queue is empty will end the loop
					break;
				}
				block = memory;
				i++; //increments "time"
			}
			else if(line->size > block->size || block->type == 1)
			{
				//if no space in the current block goes to next block in memory
				if(block->next == NULL)
				{
					//if there is no next block will remove the process that has been there the longest and starts from the beginning
					removemem();
					block = memory;
				}
				else
				{
					block = block->next;
				}
			}
		}
		printf("Total loads: %d, average #processes = %.1f, average #holes = %.1f, cumulative %%mem = %.1f\n", i, (totproc/i), (tothole/i), permem);
		
		//deletes the memory for new allocation
		memory = empty(memory);
		
		//initializes queue and times removed
		for(i = 0; i < num; i++)
		{
			insertq(size[i], name[i]);
			timesremoved[i] = 0;
		}
		
		//initializes memory to empty
		if(memory == NULL)
		{
			insertmem(128, 'x', 0, 0, memory);
		}
		displaymem(memory);
		//initializes values
		totproc = 0;
		tothole = 0;
		totmem = 0;
		line = queue;
		block = memory;
		i = 1;
		j = 1;
		
		//same as first fit except block is not set to the first element in the memory every time a process is added
		printf("\n *--------Next Fit--------*\n\n");
		while(line != NULL)
		{
			line = queue;
			if(line->size <= block->size && block->type == 0)
			{
				insertmem(line->size, line->name, 1, i, block);
				countp = countprocess(memory);
				totproc = totproc + countp;
				counth = countholes(memory);
				tothole = tothole + counth;
				taken = takenspace(memory);
				memuse = taken/128.0 * 100;
				totmem = totmem + memuse;
				permem = totmem/i;
				printf("%c loaded, #processes = %.0f, #holes = %d, %%memusage = %.2f, cumulative %%mem = %.2f\n", line->name, countp, counth, memuse, permem);
				j = deleteq();
				if(j == 0)
				{
					break;
				}
				i++;
			}
			else if(line->size > block->size || block->type == 1)
			{
				if(block->next == NULL)
				{
					removemem();
					block = memory;
				}
				else
				{
					block = block->next;
				}
			}
		}
		printf("Total loads: %d, average #processes = %.1f, average #holes = %.1f, cumulative %%mem = %.1f\n", i, (totproc/i), (tothole/i), permem);
		
		//clears memory for new allocation method
		memory = empty(memory);
		
		//initializes values and memory
		for(i = 0; i < num; i++)
		{
			insertq(size[i], name[i]);
			timesremoved[i] = 0;
		}
		
		if(memory == NULL)
		{
			insertmem(128, 'x', 0, 0, memory);
		}
		
		totproc = 0;
		tothole = 0;
		totmem = 0;
		line = queue;
		block = memory;
		i = 1;
		j = 1;
		best = 0;
		struct mem *temp;
		
		printf("\n*--------Best Fit--------*\n\n");
		while(line != NULL)
		{
			space = 0; //int for if there is a place in memory that fits the new process
			line = queue;
			block = memory;
			//checks each block to see if the new process can fit
			while(block != NULL)
			{
				//if process will fit in block
				if(line->size <= block->size && block->type == 0)
				{
					if(space == 0)
					{
						//sets best as the space that will be left in memory
						best = block->size - line->size;
						temp = block; //saves the location for the best block to fit process
						space++; //increments space
					}
					else if(best > (block->size - line->size))
					{
						//if block size is better than the current best, it will be replaces
						best = block->size - line->size;
						temp = block;
					}
				}
				//goes to next block
				block = block->next;
			}
			if(space == 0)
			{
				//if there was no place the process would fit removes a block from memory
				removemem();
			}
			else
			{
				//inserts process into best block
				insertmem(line->size, line->name, 1, i, temp);
				//calculates all needed values
				countp = countprocess(memory);
				totproc = totproc + countp;
				counth = countholes(memory);
				tothole = tothole + counth;
				taken = takenspace(memory);
				memuse = taken/128.0 * 100;
				totmem = totmem + memuse;
				permem = totmem/i;
				printf("%c loaded, #processes = %.0f, #holes = %d, %%memusage = %.2f, cumulative %%mem = %.2f\n", line->name, countp, counth, memuse, permem);
				j = deleteq();//deletes the process from the queue after it has been added to memory;
				if(j == 0)
				{
					break;
				}
				i++;
			}
		}
		printf("Total loads: %d, average #processes = %.1f, average #holes = %.1f, cumulative %%mem = %.1f\n", i, (totproc/i), (tothole/i), permem);
		
		
		//clears memory for new allocation method
		memory = empty(memory);
		
		//initializes all values
		for(i = 0; i < num; i++)
		{
			insertq(size[i], name[i]);
			timesremoved[i] = 0;
		}
		
		if(memory == NULL)
		{
			insertmem(128, 'x', 0, 0, memory);
		}
		
		totproc = 0;
		tothole = 0;
		totmem = 0;
		line = queue;
		block = memory;
		i = 1;
		j = 1;
		best = 0;
		
		//same as best fit except best will be changed if the next block is bigger
		printf("\n*--------Worst Fit--------*\n\n");
		while(line != NULL)
		{
			space = 0;
			line = queue;
			block = memory;
			while(block != NULL)
			{
				if(line->size <= block->size && block->type == 0)
				{
					if(space == 0)
					{
						best = block->size - line->size;
						temp = block;
						space++;
					}
					else if(best < (block->size - line->size))
					{
						best = block->size - line->size;
						temp = block;
					}
					
				}
				block = block->next;
			}
			if(space == 0)
			{
				removemem();
			}
			else
			{
				insertmem(line->size, line->name, 1, i, temp);
				countp = countprocess(memory);
				totproc = totproc + countp;
				counth = countholes(memory);
				tothole = tothole + counth;
				taken = takenspace(memory);
				memuse = taken/128.0 * 100;
				totmem = totmem + memuse;
				permem = totmem/i;
				printf("%c loaded, #processes = %.0f, #holes = %d, %%memusage = %.2f, cumulative %%mem = %.2f\n", line->name, countp, counth, memuse, permem);
				j = deleteq();
				if(j == 0)
				{
					break;
				}
				i++;
			}
		}
		printf("Total loads: %d, average #processes = %.1f, average #holes = %.1f, cumulative %%mem = %.1f\n", i, (totproc/i), (tothole/i), permem);
	}
	
	//clears memory
	memory = empty(memory);
	
return 0;	
}
