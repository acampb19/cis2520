#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int heap[10];/*heap array*/

/*function to sort heap*/
void sort(int height)
{
    int i, s, f, temp;/*variables and counters*/
    for (i = height - 1; i > 0; i--)
    {
        temp = heap[i];/*sets current heap element to a temp value*/
        heap[i] = heap[0];/*moves element to top of heap*/
        f = 0;

        if (i == 1)
        {
			s = -1;
		}
        else
        {
			s = 1;
		}

        if (i > 2 && heap[2] > heap[1])
        {
			s = 2;
		}

        while (s >= 0 && temp < heap[s])
        {
            heap[f] = heap[s];
            f = s;
            s = 2 * f + 1;

            if (s + 1 <= i - 1 && heap[s] < heap[s + 1])
                s++;
            if (s > i - 1)
                s = -1;
        }
        heap[f] = temp;
    }
}
/*function to make the array*/
void make(int array[20][11], char * line, int height)
{
	char * token;/*token to split up the string input*/
	int i = 0;/*counter*/
	
	token = strtok(line, " ");/*tokenizes string for spaces*/
	
	while(token != NULL)
	{
		array[height][i] = atoi(token);/*takes value and puts it into the array*/
		token = strtok(NULL, " ");
		i++;/*increments so no value is overwritten*/
	}
	array[height][i] = array[height][0] + array[height][1] + array[height][2]; /*calculates the key and puts it into the 10th spot of the array*/
}
         
/*function to display heap*/
void display(int height)
{
	int i; /*counter*/
    if (height == 0)
    {
		/*checks if heap is empty*/
        printf("Heap is empty \n");
        return;
    }

    for (i = 0; i < height; i++)
	{
		/*printd each element in the heap*/
        printf("%d ", heap[i]);
	}
    printf("\n");

}

/*function to insert element into the heap*/
void insert(int num, int location)
{
	int parentnode;/*location of parent node*/
	
    while (location > 0)/*while still elements in the heap*/
    {
        parentnode = (location - 1)/2;
        if (num <= heap[parentnode]) /*adds element to the heap*/
        {
            heap[location] = num;
            return;
        }
        heap[location] = heap[parentnode]; /*sets heap location and parent node equal*/
        location = parentnode;
    }
    heap[0] = num; /*sets first element in heap to the array number*/
}

int main(void)
{
	int height = 0; /*variable for height*/
	int i = 0; /*counter*/
	int j = 0;
	char line [50]; /*array for input*/
	int array[20][11]; /*2d array for input*/
	FILE * point = fopen("f.dat", "r");/*opens file for reading*/
	
	if(point == NULL)
	{
		/*checks if file was opened*/
		printf("Error opening file\n");
		return 0;
	}
	
	while(fgets(line, sizeof(line), point))
	{
		/*if file was opened gets each line and puts it into the 2d array*/
		make(array, line, j);
		j++; /*increments*/
	}
	fclose(point);/*closes file*/

	for(i = 0; i < 20; i++)
	{
		insert(array[i][10], height);
		height++; /*counts height*/
	}
	sort(height); /*sorts heap*/
	display(height); /*displays heap*/
	
return 0;	
}
