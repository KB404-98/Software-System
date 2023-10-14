/*
=====================================================================================================================================
Name : Progaram21_read.c
Author : Kuldip Nivruti Bhatale
Roll No : MT2023087
Description : Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 9th Oct, 2023.
=====================================================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {

    	int fd1, fd2; // File descriptors for the FIFOs
    	char buff1[256]; // Buffer for reading
    	char buff2[256]; // Buffer for writing

   	 // Open the FIFO for reading
   	 fd1 = open("myfifo1", O_RDONLY);
   	 if (fd1 == -1) {
        	perror("open for reading");
        	exit(EXIT_FAILURE);
    	}

    	// Open the FIFO for writing
    	fd2 = open("myfifo2", O_WRONLY);
    	if (fd2 == -1) {
        	perror("open for writing");
        	close(fd1); // Close the first FIFO
        	exit(EXIT_FAILURE);
    	}

    	// Read data from the first FIFO
    	ssize_t bytesRead = read(fd1, buff1, sizeof(buff1));

    	if (bytesRead == -1) {
        	perror("read");
        	close(fd1); // Close the first FIFO
        	close(fd2); // Close the second FIFO
        	exit(EXIT_FAILURE);
    	}

    	// Null-terminate the received data
    	buff1[bytesRead] = '\0';

    	printf("Received from FIFO1: %s\n", buff1);

	printf("Enter the text: ");
    	scanf(" %[^\n]", buff2);

    	// Write to the second FIFO
   	 write(fd2, buff2, strlen(buff2) + 1);

    	// Close both FIFOs
    	close(fd1);
    	close(fd2);

    	return 0;
}

