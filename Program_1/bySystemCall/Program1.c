============================================================================
Name : Program 1
Author : Kuldip Nivruti Bhatale
Roll No : MT2023087
Description : Create the following types of a files using system calls
	     a. soft link (symlink system call)
	     b. hard link (link system call)
	     c. FIFO (mkfifo Library Function or mknod system call)
Date: 25th Aug, 2023.
============================================================================				


#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(){

	int v = symlink("temp.txt","destSL");
	if(v<0)
		{perror(" failed "); return 1;}

	int f = link("temp.txt", "destHL");
	if(f<0)
		{perror(" Failed "); return 1;}

	int e = mknod("destFIFO",S_IFIFO, 0);
	if(e<0)
		perror("Failed ");
	return 0;
}
