/*
==============================================================================================================
Name : Program6.c
Author : Kuldip Nivruti Bhatale
Roll No : MT2023087
Description : Write a program to take input from STDIN and display on STDOUT. Use only read/write system call 
Date: 25th Aug, 2023.
==============================================================================================================
*/

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

int main(){

	char buf[20];

	read(0,buf,20);
	write(1,buf,20);

	return 0;
}
