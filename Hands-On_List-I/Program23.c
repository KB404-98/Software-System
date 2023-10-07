/*
================================================================================
Name : Program23.c
Author : Kuldip Nivruti Bhatale
Roll No : MT2023087
Description : Write a program to create a Zombie state of the running program.
Date: 8th Sep, 2023.
================================================================================
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

		
		printf("In parent\n");
		printf("Parent process id : %d\n", getpid());
		printf("Child process id : %d\n", k);

		sleep(30);


	}
	else{

		printf("Error\n");
	}



	
}


