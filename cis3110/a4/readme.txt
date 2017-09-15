Alexandra Campbell
0789478
Assignment #4
November 24th, 2014

notes:
my program sorts a bit differently than the code that was used to get the sample output that was posted on the moodle page, and therefore the height is 13 instead of 12
my code sorts the numbers from smallest flr to largest wrn while the example code has some smaller values of flr amongst the larger values
also when reading from the file the code takes the newline at the end of the file, every time I tried to fix it it would mess up the code



How to run the program:
- Compile the program by typeing make in the command line
- Next user must enter ./avltree to run the program for the AVL tree
- user will be prompted by 7 options; 1. Initialization 2. Find 3. Insert 4. Remove 5. Check Height and Size 6. Find All (above a given frequency) and 7. Exit
- user must press key of desired action before pressing enter
		- if user presses 2-6 before pressing 1, user will recieve an error message and will be brought back to the options
- if user chooses 1 they will be prompted to enter a file name
- if user chooses 2 they will be prompted to enter a key they wish to find
- if user chooses 3 they will be prompted to enter a key they wish to insert
- if user enters a 4 they will be prompted to enter a key they wish to remove
- if user enters a 5 the program will print out the height and size of the tree
- if user enters a 6 they will be prompted to enter a frequency
- if user enters a 7 the program will terminate. 

Output Demonstration:

make
./avltree

Welcome to the AVL tree Creator
Creator: Alexandra Campbell 0789478
1. Initialization
2. Find
3. Insert
4. Remove
5. Check Height and Size
6. Find All (above a given frequency)
7. Exit
avl/> 1
Filename: A4_data_file.dat

1. Initialization
2. Find
3. Insert
4. Remove
5. Check Height and Size
6. Find All (above a given frequency)
7. Exit
avl/> 2
Find Key: flr523
Key: flr523 Frequency: 210

1. Initialization
2. Find
3. Insert
4. Remove
5. Check Height and Size
6. Find All (above a given frequency)
7. Exit
avl/> 3
Insert key: flr523
Key: flr523 Frequency 211

1. Initialization
2. Find
3. Insert
4. Remove
5. Check Height and Size
6. Find All (above a given frequency)
7. Exit
avl/> 4
Remove key: flr523

1. Initialization
2. Find
3. Insert
4. Remove
5. Check Height and Size
6. Find All (above a given frequency)
7. Exit
avl/> 2
Find Key: flr523
no such key

1. Initialization
2. Find
3. Insert
4. Remove
5. Check Height and Size
6. Find All (above a given frequency)
7. Exit
avl/> 5
Height: 13 Size: 1482

1. Initialization
2. Find
3. Insert
4. Remove
5. Check Height and Size
6. Find All (above a given frequency)
7. Exit
avl/> 6
Frequency: 9700
Key: flr2910 Frequency: 9790

1. Initialization
2. Find
3. Insert
4. Remove
5. Check Height and Size
6. Find All (above a given frequency)
7. Exit
avl/> 7
Goodbye