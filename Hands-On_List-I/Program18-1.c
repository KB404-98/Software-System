/*
=============================================================================================================
Name : Program18-1.c
Author : Kuldip Nivruti Bhatale
Roll No : MT2023087
Description : Write a program to perform Record locking.
Create three records in a file. Whenever you access a particular record, first lock it then modify/access
to avoid race condition.
 
Date: 1st Sep, 2023.
=============================================================================================================
*/


#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

struct data {
	int val;
};

int main() {
	int fd = open("record.txt", O_WRONLY);
	struct data r1, r2, r3;
	r1.val = 1;
	r2.val = 2;
	r3.val = 3;
	write(fd, &r1, sizeof(r1));
	write(fd, &r2, sizeof(r2));
	write(fd, &r3, sizeof(r3));
	close(fd);
	return 0;
} 
