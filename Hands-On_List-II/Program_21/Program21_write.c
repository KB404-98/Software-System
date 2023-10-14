/*
=====================================================================================================================================
Name : Progaram21_write.c
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
    char buff1[256]; // Buffer for writing
    char buff2[256]; // Buffer for reading

    // Open the FIFO for writing
    fd1 = open("myfifo1", O_WRONLY);
    if (fd1 == -1) {
        perror("open for writing");
        exit(EXIT_FAILURE);
    }

    // Open the FIFO for reading
    fd2 = open("myfifo2", O_RDONLY);
    if (fd2 == -1) {
        perror("open for reading");
        close(fd1); // Close the first FIFO
        exit(EXIT_FAILURE);
    }

    printf("Enter the text: ");
    scanf(" %[^\n]", buff1);

    // Write the user input to the first FIFO
    write(fd1, buff1, strlen(buff1) + 1);

    // Read data from the second FIFO
    ssize_t bytesRead = read(fd2, buff2, sizeof(buff2));

    if (bytesRead == -1) {
        perror("read");
        close(fd1); // Close the first FIFO
        close(fd2); // Close the second FIFO
        exit(EXIT_FAILURE);
    }

    // Null-terminate the received data
    buff2[bytesRead] = '\0';

    printf("The text from FIFO file: %s\n", buff2);

    // Close both FIFOs
    close(fd1);
    close(fd2);

    return 0;
}

