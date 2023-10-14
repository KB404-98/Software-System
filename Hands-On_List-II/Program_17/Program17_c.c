/*
=====================================================================================================================================
Name : Progaram17_c.c
Author : Kuldip Nivruti Bhatale
Roll No : MT2023087
Description : Write a program to execute ls -l | wc a. use fntl
Date: 8th Oct, 2023.
=====================================================================================================================================
*/	


#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main() {

	int fd[2];

	pipe(fd);

	if (!fork()) {
		
		close(1); // close STDOUT
		close(fd[0]);
		fcntl(fd[1], F_DUPFD, 1);
		execlp("ls", "ls", "-l", (char*) NULL);
		// execlp() will write output of "ls -l" to fd with value = 1	(write-end of pipe)
	}
	else {
		close(0); // close STDIN
		close(fd[1]);
		fcntl(fd[0], F_DUPFD, 0);
		execlp("wc", "wc", (char*) NULL);
		// execlp() will read input from fd with value = 0 (read-end of	pipe) as input to “wc” command and show output to fd with value = 1 =>STDOUT
	}
}
