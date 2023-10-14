/*
=====================================================================================================================================
Name : Progaram23.c
Author : Kuldip Nivruti Bhatale
Roll No : MT2023087
Description :Write a program to print the maximum number of files can be opened within a process and size of a pipe (circular buffer).
Date: 10th Oct, 2023.
=====================================================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>



int main() {
   	 // Get the maximum number of files that can be opened within a process
   	 long fileCnt = sysconf(_SC_OPEN_MAX);
   	
	
	 if (fileCnt == -1) {
        	perror("sysconf");
        	exit(EXIT_FAILURE);
   	 }

   	
	 printf("Maximum number of files that can be opened: %ld\n", fileCnt);

    	
	 
	 
	 // Create a pipe to get the size of a pipe (circular buffer)
    	int fd[2];
    	if (pipe(fd) == -1) {
       		 perror("pipe");
       		 exit(EXIT_FAILURE);
    	}

   	 // Get the pipe buffer size
    	long pipeSize = fpathconf(fd[0], _PC_PIPE_BUF);
    	if (pipeSize == -1) {
        	perror("fpathconf");
        	exit(EXIT_FAILURE);
    	}

    	printf("Size of a pipe (circular buffer): %ld bytes\n", pipeSize);

   	 return 0;
}

