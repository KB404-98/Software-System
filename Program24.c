/*
============================================================================
Name : Program24.c
Author : Kuldip Nivruti Bhatale
Roll No : MT2023087
Description : Write a program to create an orphan process.
Date: 8th Sep, 2023.
============================================================================
*/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>


int main(){


	pid_t k;

	k = fork();

	if(k == 0){
		sleep(60);
		printf("In child\n Child Process ID : %d \n Parent Process ID : %d \n",getpid(),getppid());
	
	}

	else if (k > 0){

		printf("In parent\n Parent Process ID : %d \n Child process ID : %d \n", getpid(),k);
				sleep(10);
	}
	else{
		perror("Error");
	}
	return 0;


}


