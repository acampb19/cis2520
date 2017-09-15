#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node
{
	char * element;
	int count; 
	int height;
	int bf;
	struct node *left,*right;
};
 
/*function to get height of the tree*/
int height(struct node * tree)
{
    if (tree == NULL)
    {
        return 0;
	}
	else
    {
		return tree->height;
	}
}
 
/* A function to get maximum of two integers*/
int max(int num1, int num2)
{
	if(num1 > num2)
	{
		return num1;
	}
	else
	{
		return num2;
	}
}

struct node * minValueNode(struct node* tree)
{
    struct node* current = tree;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
    {
		current = current->left;
	}
 
return current;
}
/*function to print out the tree nodes in order*/
void inOrder(struct node *root)
{
    if(root != NULL)
	{
		inOrder(root->left);/*recursively prints out left operand*/
		printf("element: %s balance: %d height: %d count: %d\n",root->element, root->bf, root->height, root->count);/*prints out element at this location*/
		inOrder(root->right);/*recursively prints out right operand*/
	}
}

/*function to create new tree node*/
struct node * newNode(char * key)
{
    struct node * tree = malloc(sizeof(struct node)); /*allocates memory for node*/
    tree->element = key; /*sets node equal to the key*/
    tree->left = malloc(sizeof(struct node)); /*allocates memory for left node*/
	tree->right = malloc(sizeof(struct node)); /*allocates memory for right node*/
    tree->left = NULL; /*sets left and right nodes to null*/
    tree->right = NULL;
    tree->height = 0;  //initialize heigh as 1
    tree->count = 1;
    tree->bf = 0;
    return(tree); /*returns new node*/
}

/*function to rotate tree right*/
struct node *rightRotate(struct node * tree)
{
    struct node * nodeL = tree->left;
    struct node * nodeR = nodeL->right;
 
    // Perform rotation
    nodeL->right = tree;
    tree->left = nodeR;
 
    // Update heights
    tree->height = max(height(tree->left), height(tree->right))+1;
    nodeL->height = max(height(nodeL->left), height(nodeL->right))+1;
 
    // Return new root
    return nodeL;
}
 
/*function to rotate left*/
struct node *leftRotate(struct node * tree)
{
    struct node * nodeR = tree->right;
    struct node *nodeL = nodeR->left;
 
    // Perform rotation
    nodeR->left = tree;
    tree->right = nodeL;
 
    //  Update heights
    tree->height = max(height(tree->left), height(tree->right))+1;
    nodeR->height = max(height(nodeR->left), height(nodeR->right))+1;
 
    // Return new root
    return nodeR;
}
 
// Get Balance factor of node 
int getBalance(struct node * tree)
{
    if (tree == NULL)
    {
        return 0;
	}
	else
    {
		return height(tree->left) - height(tree->right);
	}
}

/*function to insert nodes into tree*/
struct node * insert(struct node* node, char * key)
{

	int num1 = 0; /*ints to hold integer values from keys*/
	int num2 = 0;
	int numL = 0;
	int numR = 0;
    if (node == NULL)
    {
        return(newNode(key));
	}
    else 
    {
		if(strstr(key, "wrn"))
		{
			num1 = 10000 * atoi(key+3);/*makes sure wrn is always bigger than flr*/
		}
		else
		{
			num1 = atoi(key+3);
		}
		if(strstr(node->element, "wrn"))
		{
			num2 = 10000 * atoi(node->element+3);/*makes sure wrn is always bigger than flr*/
		}
		else
		{
			num2 = atoi(node->element+3);
		}
		
		if(num1 < num2)
		{
			/*if key is smaller than the node, go to left branch*/
			node->left  = insert(node->left, key);
		}
		else if(num1 > num2)
		{
			/*if key is larger than the node, go to right branch*/
			node->right = insert(node->right, key);
		}
		else if(num1 == num2)
		{
			/*if node and key are equal, increment the frequency*/
			node->count++;
		}
	}
	
	/* updates height */
    node->height = max(height(node->left), height(node->right)) + 1;
 
    /* Gets the balance factor*/
    int balance = getBalance(node);
	node->bf = balance;
	
    /*if node is unbalanced, will rotate tree*/
    if(node->left != NULL)
	{
		if(strstr(node->left->element, "wrn"))
		{	
			numL = 10000 * atoi(node->left->element+3);/*makes sure wrn is always bigger than flr*/
		}
		else
		{
			numL = atoi(node->left->element+3);
		}
	}
	if(node->right != NULL)
	{
		if(strstr(node->right->element, "wrn"))
		{
			numR = 10000 * atoi(node->right->element+3);/*makes sure wrn is always bigger than flr*/
		}
		else
		{
			numR = atoi(node->right->element+3);
		}
	}
    /* Left Left Case*/
    if (balance > 1 && num1 < numL)
    {
		return rightRotate(node);
	}
    /* Right Right Case*/
    if (balance < -1 && num1 > numR)
    {
		return leftRotate(node);
	}
    /* Left Right Case*/
    if (balance > 1 && num1 > numL)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
    /* Right Left Case*/
    if (balance < -1 && num1 < numR)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
	
    return node;
}

/*function to make the tree*/
struct node * initialize(struct node * root)
{
	char line [300]; /*hols file line*/
	char * tree [50000]; /*array to hold every file line*/
	char * token; /*token for tokenizing strings*/
	int i = 0; /*counters*/
	int j = 0;
	char filename[20]; /*string for user inputted file name*/
	printf("File name: "); /*user prompt*/
	scanf("%s", filename); /*reads in uer input*/
	FILE * file = fopen(filename, "r");/*opens file for reading*/
	
	if(file == NULL)
	{	
		printf("Error opening file\n");
		return NULL;
	}
	
	while(fgets(line, sizeof(line), file)) /*gets every line of the file and stores in tree array*/
	{
		tree[i] = malloc(sizeof(line));
		strcpy(tree[i], line);
		i++;/*counts how many lines*/
	}
	fclose(file);/*closes file*/
	
	for(j=0;j < i; j++)
	{
		token = strtok(tree[j], " "); /*tokenizes each string in tree*/
		
		while(token != NULL)
		{
			if(strlen(token) > 3)
			{
				if(root == NULL)
				{
					root = newNode(token); /*if first node, just creates node by sending token to newNode function*/
				}
				else
				{
					root = insert(root, token); /*sends token and root to insert function*/
				}
			}
			token = strtok(NULL, " ");
		}
	}
	for(j=0;j<i; j++)
	{
		free(tree[i]);
	}
	/*inOrder(root);*/
return root;	
}

int find_key (struct node * tree, char * inkey, int i)
{
	if(tree != NULL)
	{
		i = find_key(tree->left, inkey, i);/*recursively checks left node*/
		if(strcmp(inkey, tree->element) == 0)
		{
			printf("Key: %s Frequency: %d\n", tree->element, tree->count);
			return 1;
		}
		 i = find_key(tree->right, inkey, i);/*recursively checks right node*/
	}
return i;	
}

void find_freq (struct node * tree, int frequency)
{
	if(tree != NULL)
	{
		find_freq(tree->left, frequency);/*recursively prints out left operand*/
		if(tree->count > frequency)
		{
			printf("Key: %s Frequency: %d\n", tree->element, tree->count);
		}
		find_freq(tree->right, frequency);/*recursively prints out right operand*/
	}
}

struct node* deleteNode(struct node* root, char * key)
{
	int num1 = 0;
	int num2 = 0;
    if (root == NULL)
    {
		return root;
	}
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    else
    {
		if(strstr(key, "wrn"))
		{
			num1 = 10000 * atoi(key+3);/*makes sure wrn is always bigger than flr*/
		}
		else
		{
			num1 = atoi(key+3);
		}
		if(strstr(root->element, "wrn"))
		{
			num2 = 10000 * atoi(root->element+3);/*makes sure wrn is always bigger than flr*/
		}
		else
		{
			num2 = atoi(root->element+3);
		}
		if ( num1 < num2 )
		{
			root->left = deleteNode(root->left, key);
		}
	 
		// If the key to be deleted is greater than the root's key,
		// then it lies in right subtree
		else if( num1 > num2 )
		{
			root->right = deleteNode(root->right, key);
		}
		// if key is same as root's key, then This is the node
		// to be deleted
		else
		{
			// node with only one child or no child
			if( (root->left == NULL) || (root->right == NULL) )
			{
				struct node *temp = root->left ? root->left : root->right;
	 
				// No child case
				if(temp == NULL)
				{
					temp = root;
					root = NULL;
				}
				else // One child case
				{
					*root = *temp; // Copy the contents of the non-empty child
				}
	 
				free(temp);
			}
			else
			{
				// node with two children: Get the inorder successor (smallest
				// in the right subtree)
				struct node* temp = minValueNode(root->right);
	 
				// Copy the inorder successor's data to this node
				root->element = temp->element;
	 
				// Delete the inorder successor
				root->right = deleteNode(root->right, temp->element);
			}
		}
	}
 
    // If the tree had only one node then return
    if (root == NULL)
    {
		return root;
	}
 
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = max(height(root->left), height(root->right)) + 1;
 
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether
    //  this node became unbalanced)
    int balance = getBalance(root);
	root->bf = balance;
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
    {
		return rightRotate(root);
	}
 
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
    {
		return leftRotate(root);
	}
 
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
return root;
}
int size(struct node * tree)
{
	int i;
	if(tree == NULL)
	{
		i = 0;
	}
	else if(tree != NULL)
	{
		i = 1 + size(tree->left) + size(tree->right);
	}
return i;	
}
int main(void)
{
	char * inkey = malloc(sizeof(char *));
	char * key = malloc(sizeof(char *));
	char * remkey = malloc(sizeof(char *));
	int choice = 0; /*int to hold user choice*/
	int frequency = 0;
	int i;
	struct node * root = NULL; /*node for root of tree*/
	
	printf("Welcome to the AVL tree Creator\nCreator: Alexandra Campbell 0789478"); /*header*/
	
	/*while statement to loop until user enters a 7*/
	while(choice != 7)
	{
		printf("\n1. Initialization\n2. Find\n3. Insert\n4. Remove\n5. Check Height and Size"); /*user prompts*/
		printf("\n6. Find All (above a given frequency)\n7. Exit\navl/> ");
		scanf("%d", &choice); /* scans in user input*/
		
		if(choice == 1)
		{
			/*if choice is 1, will initialize the tree*/
			root = initialize(root);
		}
		else if(choice == 2)
		{
			if(root == NULL)
			{
				printf("You must initialize the tree first\n");
			}
			else
			{
				printf("Find Key: ");
				scanf("%s", key);
				i = find_key(root, key, 0);
				if(i == 0)
				{
					printf("no such key\n");
				}
			}
		}
		else if(choice == 3)
		{
			if(root == NULL)
			{
				printf("You must initialize the tree first\n");
			}
			else
			{
				printf("Insert key: ");
				scanf("%s", inkey);
				insert(root, inkey);
				find_key(root, inkey, 0);
			}
		}
		else if(choice == 4)
		{
			if(root == NULL)
			{
				printf("You must initialize the tree first\n");
			}
			else
			{
				printf("Remove key: ");
				scanf("%s", remkey);
				root = deleteNode(root, remkey);
			}
		}
		else if(choice == 5)
		{
			if(root == NULL)
			{
				printf("You must initialize the tree first\n");
			}
			else
			{
				printf("Height: %d Size: %d\n", root->height, size(root));
			}
		}
		else if(choice == 6)
		{
			if(root == NULL)
			{
				printf("You must initialize the tree first\n");
			}
			else
			{
				printf("Frequency: ");
				scanf("%d", &frequency);
				find_freq(root, frequency);
			}
		}
		else if(choice == 7)
		{
			printf("Goodbye\n");
			free(key);
			free(inkey);
			free(remkey);
		}
		else
		{
			printf("Invalid entry, please choose one of the following:\n");
		}
	}
return 0;
}
