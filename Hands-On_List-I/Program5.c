/*
=================================================================================================================
Name : Program5.c
Author : Kuldip Nivruti Bhatale
Roll No : MT2023087
Description : Write a program to create five new files with infinite loop. Execute the program in the background
and check the file descriptor table at /proc/pid/fd 
Date: 25th Aug, 2023.
Output : run command as ls -l /proc/processid/fd
=================================================================================================================
*/


#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>


int main()
{
	int fd1,fd2,fd3,fd4,fd5;
	fd1=creat("file1",O_RDONLY);
	fd2=creat("file2",O_RDONLY);
	fd3=creat("file3",O_RDONLY);
	fd4=creat("file4",O_RDONLY);
	fd5=creat("file5",O_RDONLY);
	for(;;);

}
