/*
======================================================================================================
Name : Program29.c
Author : Kuldip Nivruti Bhatale
Roll No : MT2023087
Description : Write a program to get scheduling policy and modify the scheduling policy (SCHED_FIFO,
SCHED_RR)
Date: 8th Sep, 2023.
=====================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>

int main() {

    int pid=getpid(); 
    int policy;
    struct sched_param param;

    policy = sched_getscheduler(pid);

    if (policy == -1) {
        perror("Error");
        return 0;
    }

    switch (policy) {
        case SCHED_FIFO:
            printf("Scheduling policy: SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("Scheduling policy: SCHED_RR\n");
            break;
        case SCHED_OTHER:
            printf("Scheduling policy: SCHED_OTHER\n");
            break;
        default:
            printf("Scheduling policy: Unknown\n");
            break;
    }

    printf("1. Want to set scheduling policy to SCHED_FIFO\n");
    printf("2. Want to set scheduling policy to SCHED_RR\n");
    printf("3. Quit\n");
    printf("Enter your choice: ");

    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        policy = SCHED_FIFO;
    } else if (choice == 2) {
        policy = SCHED_RR;
    } else if (choice == 3) {
        return 1;
    } else {
        printf("Invalid choice\n");
        return 1;
    }

    //it's common practice to set the priority to the maximum possible value to ensure that the process has the highest priority within its scheduling policy class

    param.sched_priority = sched_get_priority_max(policy);

    if (sched_setscheduler(pid, policy, &param) == -1) {
        perror("Error");
        return 1;
    }

    printf("Scheduling policy for process with PID %d set to ", pid);

    switch (policy) {
        case SCHED_FIFO:
            printf("Scheduling policy: SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("Scheduling policy: SCHED_RR\n");
            break;
        case SCHED_OTHER:
            printf("Scheduling policy: SCHED_OTHER\n");
            break;
        default:
            printf("Scheduling policy: Unknown\n");
            break;
    }

    return 1;
}

