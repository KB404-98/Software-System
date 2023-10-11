#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    	int shmid;
    	char *data;

    	// Create a key to identify the shared memory segment
    	key_t key = ftok(".", 'c');
    	
	if (key == -1) {
        	perror("ftok");
        	exit(1);
    	}

    	// Create a shared memory segment of size 1024 bytes
    	shmid = shmget(key, 1024, IPC_CREAT | 0744);
    	
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

    	// Prompt the user to enter text
    	printf("Enter the text: ");
    	fgets(data, 1024, stdin);

    	// Display the entered text
    	printf("You entered: %s\n", data);

    	// Detach the shared memory segment from the process
    	if (shmdt(data) == -1) {
        	perror("shmdt");
        	exit(1);
    	}

    	return 0;

}

