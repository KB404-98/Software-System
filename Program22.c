/*
=====================================================================================================================================
Name : Progaram22.c
Author : Kuldip Nivruti Bhatale
Roll No : MT2023087
Description : Write a program, open a file, call fork, and then write to the file by both the child as well as the parent processes. 
Check output of the file
Date: 8th Sep, 2023.
=====================================================================================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<string.h>


int main(){

	int fd, p;
       
	fd = open("temp.txt", O_RDWR | O_CREAT , 0777);

	if(fd < 0){

		perror("ERROR");
		return 1;
	}


	pid_t k = fork();

	if(k == 0){

		printf("In child process.\n");
		char a[] = "\nThis is written by child\n";
		write(fd, a, sizeof(a));
	}
	else if(k > 0){

		wait(NULL);
		printf("In Parent Process. \n");

		char b[] = "\nThis is written by parent\n";
		write(fd, b, sizeof(b));
	}
	else{
		perror("Error");

	}


	close(fd);

	return 0;

}
