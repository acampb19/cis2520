Cis*3110 - Assignment 1
Alexandra Campbell
0789478


To compile the program enter make into the command line and press enter, then enter ./msh and enter again. The program will then wait for the user to enter a command. If the user enters "exit" the program will implement the exit() system call that ends the process. If the user enters a command with or without arguments the program will fork and print out the result. If the user enters a command followed by a &, the algorithm will fork and return without waiting for the process to complete while the process runs in the background. If the user enters a command containing the > character, the program will put the results of the process in the following filename, if the file does not exist it will make a file with that name. If the user enters a commmand containing the < the input to the function will be taken from the filename. If the user enters "add" then the program will convert hex numbers to decimal numbers and add all them all together before printing out the result. If the user enters "arg" the program will print out all of the arguments and number of arguments. If the user enters "mult" the program will multiply all the entered numbers and print out the result. 

I could not figure out how to implement the pipe function so I did not end up including it in my assignment. For the command that I designed myself, I decided to make the program multiply all of the numbers that the user enters. 

Example: mult 5 6 
Details: multiplies all numbers and outputs the result
Output = 5 * 6 = 30

My program only works for the first few entries, and I could not find a way to fix that. 
