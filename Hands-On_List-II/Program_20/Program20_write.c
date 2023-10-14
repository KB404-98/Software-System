/*
=====================================================================================================================================
Name : Progaram20_b.c
Author : Kuldip Nivruti Bhatale
Roll No : MT2023087
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 9th Oct, 2023.
=====================================================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {

	int fd; // File descriptor for the FIFO
    	char buff[256]; // Buffer for user input

    	// Open the FIFO for writing
   	 fd = open("myFifo", O_WRONLY);

   	 if (fd == -1) {
        	perror("open");
        	exit(EXIT_FAILURE);
    	}

    	printf("Enter the text: ");
    	scanf(" %[^\n]", buff);

    	// Write the user input to the FIFO
    	write(fd, buff, strlen(buff) + 1);

    	// Close the FIFO
   	 close(fd);

    return 0;
}

