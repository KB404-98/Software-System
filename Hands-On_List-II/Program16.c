/*
=====================================================================================================================================
Name : Progaram16.c
Author : Kuldip Nivruti Bhatale
Roll No : MT2023087
Description : Write a program to send and receive data from parent to child vice versa. Use two way communication.
Date: 8th Oct, 2023.
=====================================================================================================================================
*/	
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>


int main(){

	int fd1[2];  // parent to child
	int fd2[2];  // child to child

	pid_t pid;

	char pmsg[] = "Hello child, How are you?";
	char cmsg[] = "I am fine";

	char buff[100];

	if(pipe(fd1) == -1 || pipe(fd2) == -1){

		perror("Pipe");
		return 1;
	}

	pid = fork();

	if(pid == -1){
		
		perror("Fork");
		return 1;
	}

	if(pid > 0){

		close(fd1[0]);
		close(fd2[1]);

		ssize_t bytwr = write(fd1[1], pmsg, strlen(pmsg));

		if(bytwr == -1){

			perror("Write to child");
			return 1;
		}

		ssize_t bytrd = read(fd2[0], buff, sizeof(buff));

		if(bytrd == -1){

			perror("Read from child");
			return 1;

		}

		buff[bytrd] = '\0';

		printf("Message from child : %s\n", buff);

		close(fd1[1]);
		close(fd2[0]);
	

	}else{
		close(fd1[1]);
		close(fd2[0]);
		
		ssize_t bytrd = read(fd1[0], buff, sizeof(buff));

		if(bytrd == -1){
		
			perror("Read from parent");
			return 1;
		}

		buff[bytrd] = '\0';

		printf("Message from parent : %s\n", buff);

		ssize_t bytwr = write(fd2[1], cmsg, strlen(cmsg));

		if(bytwr == -1){

			perror("Write to parent");
			return 1;
		}


		close(fd1[0]);
		close(fd2[1]);

		
	}



	return 0;
}
