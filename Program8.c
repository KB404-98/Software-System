/*
=======================================================================================================================
Name : Program8.c
Author : Kuldip Nivruti Bhatale
Roll No : MT2023087
Description : Write a program to open a file in read only mode, read line by line and display each line as it is read.
Close the file when end of file is reached.
Date: 25th Aug, 2023.
=======================================================================================================================
*/
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *args[]) {
	if(argc != 2) {
		printf("Incorrect number of arguments, expected 1\n, got %d", (argc - 1));
		return -1;
	}
	int fd = open(args[1], O_RDONLY);
	if(fd == -1) {
		printf("Could not open file\n");
		return -1;
	}
	int eof = 0;
	while(!eof) {
		char buff;
		while(1) {
			int res_read = read(fd, &buff, 1);
			if(res_read == 0) {
				eof = 1;
				break;
			}
			else {
				printf("%c", buff);
				if(buff == '\n') {
					break;
				}
			}
		}
	}
	int close_fd = close(fd);
	if(close_fd == -1) {
		printf("Could not close file\n");
	}
	return 0;
}
