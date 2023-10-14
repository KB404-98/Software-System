/*
=====================================================================================================================================
Name : Progaram30_b.c
Author : Kuldip Nivruti Bhatale
Roll No : MT2023087
Description :Write a program to create a shared memory. b. attach with O_RDONLY and check whether you are able to overwrite.
Date: 10th Oct, 2023.
=====================================================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    int shmid;
    char *data;

    key_t key;


    // Specify the key for the desired shared memory segment
    key = ftok(".", 'c'); // Replace '.' and 'b' with the appropriate key information

    if (key == -1) {
        perror("ftok");
        exit(1);
    }


    // Attempt to attach to the existing shared memory segment
    shmid = shmget(key, 0, 0);

    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment to the process's address space with read-only permission
    data = shmat(shmid, NULL, SHM_RDONLY);
    if (data == (void *)-1) {
        perror("shmat");
        exit(1);
    }

    // Try to overwrite the shared memory (this should fail due to read-only permission)
    printf("Attempting to overwrite shared memory...\n");
    strncpy(data, "This should not overwrite", 1024);

    // Detach the shared memory segment from the process
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(1);
    }

    return 0;
}

