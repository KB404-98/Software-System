#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    int shmid;
    char *data;

    // Generate the key for the existing shared memory segment
    key_t key = ftok(".", 'c');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Get the shmid of the existing shared memory segment
    shmid = shmget(key, 0, 0);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach to the shared memory segment
    data = (char *)shmat(shmid, NULL, 0);
    if (data == (void *)-1) {
        perror("shmat");
        exit(1);
    }

    // Print the data from shared memory
    printf("Text from shared memory: %s\n", data);

    // Detach from the shared memory segment
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(1);
    }

    return 0;
}

