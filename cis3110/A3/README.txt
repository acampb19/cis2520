Cis*3110 - Assignment 3
Alexandra Campbell
0789478


To compile part one of the program one must type make into the command line, press enter and then enter ./philosopher and enter again while being in the a3_part1 file. The program will then wait for the user to enter a command. If the user enters "exit" the program will implement the exit() system call that ends the process. If the user enters a command such as "philosopher # #" then the program will run the dining philosophers algorithm where the number of philosophers is the first number and the number of times they eat is the second number. The program works by creating an array of all the philosophers and an array of chopsticks. The program will loop and if both the left and the right chopsticks are there, the philosopher will pick up the chopsticks by setting the array number to 0 and lock the chopsticks so no other philospher can pick them up, pick them up and eat for a random time. When finished eating the array values will be set to 1 and the chopsticks will be unlocked. However, if the user enters an argument that is invalid the program will exit. 

To compile part two of the program one must type make into the command line, press enter and then enter ./holes and enter again while being in the a3_part1 file. If the user enters "exit" the program will implement the exit() system call that ends the process. If the user enters a command such as holes [filename] the program will open the file, parse it into a name array and a size array which will then be used to make a queue using linked lists. The program will then add each process into a memory linked list one at a time until no other processes are to be added using Best Fit, Worst Fit, First Fit and Next fit memory allocations. The corresponding loads, %memory usage, total loads, total holes, total processes etc. will outputted into the compiler for each of the aforementioned allocation strategies. 

Assumptions: 
- I used linked lists for part 2
- 


