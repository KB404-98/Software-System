/*
=====================================================================================================================================
Name : Progaram19_a.c
Author : Kuldip Nivruti Bhatale
Roll No : MT2023087
Description : Create a FIFO file by a.mknod
Date: 9th Oct, 2023.
=====================================================================================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(){

	const char *filepath = "myFifo";

	int res = mknod(filepath, S_IFIFO | 0666, 0);

	if(res){

		perror("mknod");
		exit(EXIT_FAILURE);
	}

	printf("FIFO file %s made successfully.. \n", filepath);



	return 0;
}
