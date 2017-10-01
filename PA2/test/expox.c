//----------------------------------------------------
//Author: Sadie Henry
//----------------------------------------------------

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//------------------------------------------------------
//Main function
int main(int argc, char **argv)
{
	// check for number of args
  if(argc != 3) {
  	fprintf(stderr, "Usage: Must have 2 inputs (x < 1, n >= 1)\n");
		return 1;
  }

	// variables
	pid_t pid;
	int status;

	pid = fork();
	// fork unsuccessful
	if(pid < 0){
  	fprintf(stderr, "Error: Fork was unsuccessful.\n");
		return 1;
	}
	// child process
	else if(pid == 0){
		printf("Child's PID = %d\n", getpid());
		execvp("expoxch", argv);
		
	}	
	// parent process
	else {
		pid = wait(&status);
		// child exits with error
		if(WEXITSTATUS(status) != 0){
			printf("Child's exit code: %d (error)\n", status);
			printf("Parent (PID = %d): done\n", getpid());
			return 1;
		}
		// child exits successfully
		else{
			printf("Child's exit code: %d (OK)\n", status);
			printf("Parent (PID = %d): done\n", getpid());
		}
	}

	return 0;

}

