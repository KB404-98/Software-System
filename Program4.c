/*
==================================================================================================
Name : Program4.c
Author : Kuldip Nivruti Bhatale
Roll No : MT2023087
Description : Write a program to open an existing file with read write mode. Try O_EXCL flag also. 
Date: 25th Aug, 2023.
Output : File name 4.txt is being opening(create if not exist)
==================================================================================================
*/


#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>



int main()
{

	int fd = open("Existing_File", O_RDWR | O_EXCL);


	if (fd == -1) {
		
		printf("Error No : %d \n",errno);	
		
		perror("Error");

		return 1;
	}

	printf("File opened successfully.\n");

	close(fd);

	
	return 0;
}

