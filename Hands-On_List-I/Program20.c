/*
====================================================================================================
Name : Program20.c
Author : Kuldip Nivruti Bhatale
Roll No : MT2023087
Description : Find out the priority of your running program. Modify the priority with nice command.
 
Date: 1st Sep, 2023.
====================================================================================================
*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
int main(){

        
        int pr = getpriority(PRIO_PROCESS,0);

        printf("Current priority is: %d\n",pr);

        printf("Enter the nice value to change the priority: ");
        int inp;

        scanf("%d",&inp);


        int pr1 = nice(inp);

        printf("Current prioirty is: %d\n",pr1);
        
        
        return 0;
}
