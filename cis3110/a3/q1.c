#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*structure for the tree*/
struct node
{
	char * element; 
	struct node *left,*right;
};
typedef struct node nde;

/*function to create the tree*/
struct node * tree(char * inorder)
{
	struct node * root; /*node for the root of the tree*/
	root = malloc(sizeof(struct node)); /*allocates memory for each node*/
	root->left = malloc(sizeof(struct node)); /*allocates memory for left node*/
	root->right = malloc(sizeof(struct node)); /*allocates memory for right node*/
	root->left = NULL;/*initializes left node to null*/
	root->right = NULL;/*initializes right node to null*/
	int i = 0; /*counter*/
	int j = 0;/*counter*/
	root->element =  malloc(sizeof(char*)); /*allocates memory for the element*/
	char value[2]; /*temp value*/
	char * token1 = malloc(sizeof(char *)); /*allocates memory for tokens*/
	char * token2 = malloc(sizeof(char *));
	int opbracket = 0;/*counts open brackets*/
	int clbracket = 0;/*counts closed brackets*/
	
	if(inorder[0] == '(' && inorder[strlen(inorder)-1] == ')')
	{
		/*if string starts and ends with bracket do not count first one*/
		opbracket--;
	}
	for(i = 0; i < strlen(inorder); i++)
	{
		if(inorder[i] == '(')
		{
			/*counts open brackets*/
			opbracket++;
		}
		if(inorder[i] == ')')
		{
			/*counts closed brackets*/
			clbracket++;
			if(opbracket == clbracket)
			{
				if(root == NULL)
				{
					strncpy(value, &inorder[i+1], 1);
					strcpy(root->element, value);
					return root;
				}
				else
				{
					/*sets element equal to the next operator*/
					*root->element = inorder[i+1];
					root->element[1] = '\0'; /*stops string after operator*/
					strncpy(token1, inorder, i+1); /*gets string before operator*/
					token1[i+1] = '\0';
					token2 = &inorder[i+2];/*gets string after operator*/
					root->left = tree(token1+1); /*recursively finds left node*/
					root->right = tree(token2); /*recursively finds right node*/
					return root;/*returns the root value*/
				}
				
			}
		}
			
	}
	i = 0;
	if(opbracket == 0)
	{
		for(j=0; j < strlen(inorder); j++)
		{
			/*if no brackets*/
			if(inorder[j] == '+' || inorder[j] == '-' || inorder[j] == '*' || inorder[j] == '/')
			{
				/*finds next operator and sets it to root->element*/
				*root->element = inorder[j];
				root->element[1] = '\0';
				token1 = strtok(inorder, root->element);/*takes string before operator*/
				token2 = strtok(NULL, root->element);/*takes string after operator*/			
				root->left = tree(token1+1);/*recursively finds left node*/
				root->right = tree(token2); /*recursively finds right node*/
				return root;/*returns root*/
				i++;/*counts if there is an operator*/
			}
		}
		if(i == 0)
		{
			/*if no operator then scan in operands*/
			if(strstr(inorder, "x"))
			{
				/*if string contains an x the operand is a variable*/
				strncpy(value, inorder, 2);
				strcpy(root->element, value);
				root->element[2] = '\0';
				return root;
			}
			else
			{
				/*if string does not contain an x the operand is a number*/
				strncpy(value, inorder, 4);
				strcpy(root->element, value);
				root->element[4] = '\0';
				return root;
			}
		}
	}
return root;
}
/*function for preorder traversal*/
void topreorder(struct node * tree)
{
	if(tree != NULL)/*checks if node is null*/
	{
		printf("%s", tree->element);/*prints out element at this location*/
		topreorder(tree->left);/*recursively prints out left operand*/
		topreorder(tree->right);/*recursively prints out right operand*/
    }
}
/*function for postorder traversal*/
void topostorder(struct node * tree)
{
	if(tree != NULL) /*checks if node is null*/
	{
		topostorder(tree->left);/*recursively prints out left operand*/
		topostorder(tree->right);/*recursively prints out right operand*/
		printf("%s", tree->element);/*prints out element at this location*/
    }
}
/*function for inorder traversal*/
void toinorder(struct node * tree)
{
	if(tree != NULL)
	{
		printf("(");/*adds brackets around each operator and equation*/
		toinorder(tree->left);/*recursively prints out left operand*/
		printf("%s",tree->element);/*prints out element at this location*/
		toinorder(tree->right);/*recursively prints out right operand*/
		printf(")");
	}
}
/*function to update tree*/
void update(struct node * tree, char * var, char * value)
{
	char varname[2]; /*temp variable*/
	if(tree != NULL)/*checks if node is null*/
	{
		update(tree->left, var, value);/*recursively checks and updates each node*/
		strncpy(varname, tree->element, 2);/*copies variable name into temp string*/
		if(strstr(var, "x1") != NULL && strstr(varname, "x1") != NULL)/*checks if variable is x1*/
		{
			strcpy(tree->element, value);/*copies value to tree element*/
		}
		else if(strstr(var, "x2") != NULL && strstr(varname, "x2") != NULL)/*checks if variable is x2*/
		{
			strcpy(tree->element, value);/*copies value to tree element*/
		}
		else if(strstr(var, "x3") != NULL && strstr(varname, "x3") != NULL)/*checks if variable is x3*/
		{
			strcpy(tree->element, value);/*copies value to tree element*/
		}
		update(tree->right, var, value);/*recursively checks and updates each node*/
	}
}
/*function to evaluate tree*/
double calculate(struct node * tree)
{
	double num1 = 0;/*first number*/
	double num2 = 0;/*second number*/
	double val = 0;/*third number*/
	if(tree != NULL)/*checks if node is null*/
	{
		if(strstr(tree->element, "+"))
		{
			/*if operator is +, add the leaves together*/
			num1 = calculate(tree->left);
			num2 = calculate(tree->right);
			val = num1 + num2;
			return val;/*return answer*/
		}
		else if(strstr(tree->element, "-"))
		{
			/*if operator is -, subtract the leaves*/
			num1 = calculate(tree->left);
			num2 = calculate(tree->right);
			val = num1 - num2;
			return val;/*return answer*/
		}
		else if(strstr(tree->element, "*"))
		{
			/*if operator is *, multiply the leaves*/
			num1 = calculate(tree->left);
			num2 = calculate(tree->right);
			val = num1 * num2;
			return val;/*return answer*/
		}
		else if(strstr(tree->element, "/"))
		{
			/*if operator is /, divide the leaves*/
			num1 = calculate(tree->left);
			num2 = calculate(tree->right);
			if(num2 == 0)
			{
				/*if the bottom of a division is zero returns 0*/
				printf("You cannot divide by zero\n");
				return 0;
			}
			else
			{
				val = num1 / num2;
				return val;/*return answer*/
			}
			
		}
		else
		{
			/*if no operator returns leaf*/
			return atof(tree->element);
		}
	}
return val;/*return answer*/
}
/*function to print tree*/
void print_tree(struct node *tree, int j)
{
	int i; /*counter*/
	if(tree != NULL)/*checks if node is null*/
	{
		print_tree(tree->right, j+1);/*recursively prints left element*/
		for(i=0; i<j; i++)
		{
			printf("	");/*puts a space between each node*/
		} 
		printf("%s\n", tree->element);/*prints each element*/
		print_tree(tree->left, j+1);/*recursively prints right element*/
	}
}

int main(int argc, char *argv[])
{
	int choice = 0;/*user coice*/
	double total = 0;/*evaluation total of tree*/
	char input[100];/*command line input*/
	char inorder[100];/*temp value*/
	struct node * root = NULL; /*node for root of tree*/
	char newval[4];/*user input for update*/
	char varname[4];/*user input for update*/
	
	/*checks for command line argument*/
	if(argc != 2)
	{
		printf("You did not enter an equation\n");
		return 0;
	}
	strcpy(input, argv[1]);/*copies command line argument to variables*/
	strcpy(inorder, input);
	root = tree(inorder);/*builds tree*/
	/*loop to continue program until user chooses to exit*/
	while(choice != 7)
	{
		/*user prompt*/
		printf("\nWhat action would you like to perform?\n1.Display\n2.Preorder\n3.Inorder");
		printf("\n4.Postorder\n5.Update\n6.calculate\n7.Exit\n");
		scanf("%d", &choice);/*scans in user input*/
		
		if(choice == 1)
		{
			/*prints tree*/
			print_tree(root, 0);
		}
		else if(choice == 2)
		{
			/*prints preorder equation*/
			topreorder(root);
		}
		else if(choice == 3)
		{
			/*prints inorder equation*/
			toinorder(root);
		}
		else if(choice == 4)
		{
			/*prints postorder equation*/
			topostorder(root);
		}
		else if(choice == 5)
		{
			/*updates tree*/
			printf("Please enter the the value in decimal format (ex. 0.00) followed by a space and the variable you wish to change\n");
			scanf("%s %s", newval, varname);
			update(root, varname, newval);
		}
		else if(choice == 6)
		{
			/*evaluates tree*/
			total = calculate(root);
			printf("%.2f\n", total);
		}
		else if(choice == 7)
		{
			printf("You have decided to Exit\nGoodbye\n");
			
		}
		else
		{
			printf("Invalid entry, please try again\n");
		}
	}
	return 0;
}
