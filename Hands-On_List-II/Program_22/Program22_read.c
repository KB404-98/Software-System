/*
=====================================================================================================================================
Name : Progaram22_read.c
Author : Kuldip Nivruti Bhatale
Roll No : MT2023087
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select system call with FIFO..
Date: 9th Oct, 2023.
=====================================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/select.h>

int main() {
    int fd; // File descriptor for the FIFO
    char buff[256]; // Buffer for reading

    // Open the FIFO for reading
    fd = open("myFifo", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    fd_set rfds;
    struct timeval tv;
    int retval;

    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);

    tv.tv_sec = 10;
    tv.tv_usec = 0;

    retval = select(fd + 1, &rfds, NULL, NULL, &tv);

    if (retval == -1) {
        perror("select");
        close(fd);
        exit(EXIT_FAILURE);
    } else if (retval == 0) {
        printf("No data is available for reading yet\n");
    } else {
        if (FD_ISSET(fd, &rfds)) {
            printf("Data is available now\n");
            ssize_t bytesRead = read(fd, buff, sizeof(buff));
            if (bytesRead == -1) {
                perror("read");
            } else {
                buff[bytesRead] = '\0';
                printf("Data from FIFO: %s\n", buff);
            }
        }
    }

    // Close the FIFO
    close(fd);

    // Do other tasks

    return 0;
}

