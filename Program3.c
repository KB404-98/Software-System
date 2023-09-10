/*
==============================================================================================================
Name : Program3.c
Author : Kuldip Nivruti Bhatale
Roll No : MT2023087
Description : Write a program to create a file and print the file descriptor value. Use creat ( ) system call
Date: 25th Aug, 2023.
Output : File name 3.txt is created and on concole program prints File descriptor value of the file is = 3
==============================================================================================================
*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

int main(){

	int fd = creat("temp1.txt", S_IRUSR | S_IWUSR);

	if(fd == -1){
	
		printf("Error No is : %d \n", errno);
		perror("Error");
		return 1;
	}

	printf("File Created Successfully \n");

	printf("File Descriptor Value is : %d \n", fd);

	close(fd);


	return 0;
}
