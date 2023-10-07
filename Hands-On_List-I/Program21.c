/*
====================================================================================
Name : Program21.c
Author : Kuldip Nivruti Bhatale
Roll No : MT2023087
Description : Write a program, call fork and print the parent and child process id.
 
Date: 7th Sep, 2023.
====================================================================================
*/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){

	pid_t k = fork();

	if(k == 0){

		printf("In child\n");
		printf("Child process id : %d\n",getpid());
		printf("Parent process id : %d\n",getppid());
	}
	else if(k > 0){

		wait(0);
		printf("In parent\n");
		printf("Parent process id : %d\n", getpid());
		printf("Child process id : %d\n", k);
	}
	else{

		printf("Error\n");
	}



	
}
