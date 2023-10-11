#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    int shmid;
    char *data;
    key_t key;

    // Specify the key for the desired shared memory segment
    key = ftok(".", 'c'); // Replace '.' and 'c' with the appropriate key information

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

    // Attach the shared memory segment to the process's address space
    data = shmat(shmid, NULL, 0);

    if (data == (void *)-1) {
        perror("shmat");
        exit(1);
    }

    printf("Detaching shared memory segment...\n");

    // Detach from the shared memory segment
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(1);
    }

    printf("Shared memory segment detached successfully.\n");

    printf("Removing shared memory segment...\n");

    // Remove the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }

    printf("Shared memory segment removed successfully.\n");

    return 0;
}

