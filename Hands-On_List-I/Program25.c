/*
===================================================================================================================
Name : Program25.c
Author : Kuldip Nivruti Bhatale
Roll No : MT2023087
Description : Write a program to create three child processes. The parent should wait for a particular child (use
waitpid system call).
Date: 8th Sep, 2023.
===================================================================================================================
*/


#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>


int main(){
	pid_t p;
	int stat;
	printf("Before Fork\n");
	p=fork();

	if(p==0){

		printf("\nInside child 1 :: PID : %d\n", getpid());
		printf("\nParent ID of child 1 : %d\n", getppid());

	}

	else{
		pid_t q;
		printf("\nInside First : In Parent\n");
		q=fork();
		if(q==0){
			printf("\nInside child 2 :: PID : %d\n", getpid());
			printf("\nParent ID of child 2 : %d\n", getppid());
		}
		else{
			pid_t r;
			printf("\nInside Second : In Parent\n");
			r=fork();
			if(r==0){
			        sleep(10);
				printf("\nInside Child 3 :: PID : %d\n", getpid());
				printf("\nParent ID of child 3 : %d\n", getppid());
				printf("\nChild 3 completed\n");
			}
			else{
        			waitpid(r,&stat, 0);
				printf("\n\nI am Parent of all :: PID :  %d\n\n", getpid());
			}

		}		


	}	
}
