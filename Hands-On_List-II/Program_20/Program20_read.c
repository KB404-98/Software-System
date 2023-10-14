/*
=====================================================================================================================================
Name : Progaram20_a.c
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
    	char buff[256]; // Buffer for reading data

    	// Open the FIFO for reading
   	 fd = open("myFifo", O_RDONLY);

   	 if (fd == -1) {
        	perror("open");
        	exit(EXIT_FAILURE);
    	}

    	// Read data from the FIFO
    	ssize_t bytesRead = read(fd, buff, sizeof(buff));

    	if (bytesRead == -1) {
        	perror("read");
        	exit(EXIT_FAILURE);
    	}

    	// Null-terminate the received data
    	buff[bytesRead] = '\0';

    	printf("The text from FIFO file: %s\n", buff);

   	 // Close the FIFO
   	 close(fd);

    	return 0;
}

