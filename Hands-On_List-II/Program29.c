#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
	
    	key_t key;
    	int mqid;

    	// Generate the key for the existing message queue (change '.' and 'a' accordingly)
    	key = ftok(".", 'a');
    	if (key == -1) {
        	perror("ftok");
        	exit(1);
    	}

    	// Get the message queue ID
    	mqid = msgget(key, 0);
    	if (mqid == -1) {
        	perror("msgget");
        	exit(1);
    	}

    	// Remove the message queue
    	if (msgctl(mqid, IPC_RMID, NULL) == -1) {
        	perror("msgctl");
        	exit(1);
    	}

   	 printf("Message queue removed successfully.\n");

    	return 0;
}

