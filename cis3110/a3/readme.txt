Alexandra Campbell
0789478
Assignment #3
November 3rd, 2014

How to run the program:
- Compile the program by typeing make in the command line
- If user wants to create and evaluate binary expression tree type ./q1 into the command line followed by an equation
		- 	user must put '\' before each bracket to avoid errors
		-	user will be prompted with 7 options;1.Display the tree, 2.print the preorder equation, 3.print the inorder equation,
			4.print the postorder, 5.Update the tree variables, 6.calculate the tree total and 7.Exit the program
		- 	user must press key of desired action before pressing enter
		-	if user chooses 5, user will be prompted for two imputs; value and variable name
		-	user must enter the value followed by a space then the variable name (ex. 1.56 x1)
- if user wants to create a heap type ./q2 into the command line

Sample Output Demonstration:

./q1 \(\(\(x1+5.12\)-\(x2−7.68\)\)/x3\)

What action would you like to perform?
1. Display
2. Preorder
3. Inorder
4. Postorder
5. Update
6. calculate
7. Exit

1
		x3
/
				7.68
			-
				x2
	*
				5.12
			+
				x1

What action would you like to perform?
1. Display
2. Preorder
3. Inorder
4. Postorder
5. Update
6. calculate
7. Exit

2
/*+x15.12-x27.68x3

What action would you like to perform?
1. Display
2. Preorder
3. Inorder
4. Postorder
5. Update
6. calculate
7. Exit

3
((((x1)+(5.12))*((x2)-(7.68)))/(x3))

What action would you like to perform?
1. Display
2. Preorder
3. Inorder
4. Postorder
5. Update
6. calculate
7. Exit

4
x15.12+x27.68-*x3/

What action would you like to perform?
1. Display
2. Preorder
3. Inorder
4. Postorder
5. Update
6. calculate
7. Exit

5
Please enter the value in decimal format (ex. 0.00) followed by a space and the variable you wish to change
1.56 x3

What action would you like to perform?
1. Display
2. Preorder
3. Inorder
4. Postorder
5. Update
6. calculate
7. Exit

1
		1.56
/
				7.68
			-
				x2
	*
				5.12
			+
				x1
What action would you like to perform?
1. Display
2. Preorder
3. Inorder
4. Postorder
5. Update
6. calculate
7. Exit

6
-25.21

What action would you like to perform?
1. Display
2. Preorder
3. Inorder
4. Postorder
5. Update
6. calculate
7. Exit

7
You have decided to Exit
Goodbye


./q2
54 57 65 77 80 90 110 114 127 137 137 139 176 178 185 186 203 208 260
