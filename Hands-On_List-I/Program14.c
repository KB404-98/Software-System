/*
============================================================================
Name : Program14.c
Author : Kuldip Nivruti Bhatale
Roll No : MT2023087
Description : Write a program to find the type of a file.
 a. Input should be taken from command line.
 b. program should be able to identify any type of a file
Date: 28th Aug, 2023.
============================================================================
*/


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *args[]) {
	if(argc != 2) {
		printf("Expected 1 argument\n");
		return -1;
	}
	struct stat information;
	stat(args[1], &information);
	int file_type = information.st_mode & S_IFMT;
	switch(file_type) {
		case S_IFBLK:
			printf("Block file\n");
			break;
		case S_IFCHR:
			printf("Character device\n");
			break;
		case S_IFDIR:
			printf("Directory\n");
			break;
		case S_IFIFO:
			printf("FIFO\n");
			break;
		case S_IFLNK:
			printf("Symlink\n");
			break;
		case S_IFREG:
			printf("Regular\n");
			break;
		case S_IFSOCK:
			printf("Socket\n");
			break;
		default:
			printf("Unknow\n");
			break;
	}
	return 0;
}
