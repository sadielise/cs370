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
#include <math.h>

// function to calculate the factorial of a
float calculateFact(float a){
	
	float fact = 1;
	for(int i = a; i > 0; i--){
		fact = fact * i; 
	}

	return fact;

}

// function to calculate the first n terms of e^x
float calculateExp(float exp, int num){

	float retValue = 0;

	for(int i = 0; i < num; i++){
		retValue += ((powf(exp, i))/calculateFact(i));
	}

	return retValue;

}

int main(int argc, char **argv)
{
	// variables
	float x;
	int n;

	// convert arguments to float and int and check bounds
	x = atof(argv[1]);
	n = atoi(argv[2]);
	if((x <= 0) || (x >= 1) || (n < 1)){
		fprintf(stderr, "Error: Values for x, n are incorrect.\nx must be between 0 and 1, exclusive. n must be an integer greater than 0.\n");
		exit(1);
	}

	// get pid, real value, and estimated value
	pid_t pid = getpid();
	float realValue = exp(x);
	float estValue = calculateExp(x, n);

	// check difference between real and estimated values
	float diff = fabs(realValue - estValue);
	if(diff > 1){
		fprintf(stderr, "Approximation is not good\n");
		exit(1);
	}

	// print pid, real value, and estimated value
	printf("Child (PID = %d)\n", pid);
	printf("For x = %1.2f the real exp = %1.7f\n", x, realValue);
	printf("For x = %1.2f the first %d terms = %1.7f\n", x, n, estValue);

}




