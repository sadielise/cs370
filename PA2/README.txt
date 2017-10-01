Author: Sadie Henry
Date: 10/3/15
Class: CS370

This assignment includes 4 files:
- expox.c
	- contains one function (main) and executes the parent process and child process
- expoxch.c
	- contains 3 functions (main, calculateExp, calculateFact) and is called as a child process
- Makefile
	- compiles expox.c and expoxch.c into 2 separate executables, expox and expoxch
- README.txt

Program description:
expox takes 2 arguments and then forks into a child and parent process. In the child process case,
it prints the pid of the child. It does not check the values for the arguments, but simply passes them onto the child process (expoxch).
The child process, expoxch, checks the arguments and exits with a value of 1 if they are incorrect. 
It then prints its pid. It then calculates the real and estimated values for e^x. If the difference between the 2 values is
greater than 1, expoxch exits with a value of 1. When the parent is finished waiting for the child process, 
it prints the childs exit value (256 if 1, 0 if 0). It then prints it's own PID. 
