Cis*3110 - Assignment 2
Alexandra Campbell
0789478


To compile the program enter make into the command line and press enter, then enter ./msh and enter again. The program will then wait for the user to enter a command. If the user enters "exit" the program will implement the exit() system call that ends the process. If the user enters a command such as simcpu < [filename] then the program will open and parse the given file, run through all the processes and print out the total time to run the processes, the average turn around time of all the processes and the CPU utilization in a percent. However, if the user enters arguments along with the aforementioned command the program will do something different. If the user includes the -d command the program will print out a detailed list of characteristics of the processes and threads. If the user includes the -r command followed by a number the program will go into round robin scheduling mode and use the number as the quantum. Lastly, if the user enters the command -v the program will output a list of the times each thread in each phase changed states. 

Assumptions: 
- I assumed that I was to make the program print out the actual CPU usage of the device that is running the program. I made this assumption because it was not clear to me in the outline.
- I assumed that the state went from new to ready the first time the scheduler got to that process. 

Questions:
i) Yes my simulator does include overhead switch time for the first ready state to running state transition. I have made my program in such a way that an array holds whether or not the thread has been processed already. At the beginning of the program the newthread[process][thread] will be checked and if it is a 1, it will implement the overhead switch time, if the value is 0 it will not. 

ii) No it does not, it did not specify in the outline that this was a requirement and I am unsure of how to do this.

iii) No it does not, the outline said that the overhead time was to be applied to NEW threads and processes.

iv) No it does not, the outline said that the overhead time was to be applied only to NEW threads and processes.



