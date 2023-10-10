#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
	
    	key_t key;
    	int mqid;
    	struct msqid_ds msq_info;

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

    	// Display the current permissions
    	if (msgctl(mqid, IPC_STAT, &msq_info) == -1) {
        	perror("msgctl");
        	exit(1);
    	}


    	printf("Current Permissions (in octal): %o\n", msq_info.msg_perm.mode);

    	// Change the permissions
    	msq_info.msg_perm.mode = 0666; // New permissions in octal (e.g., read and write for owner, group, and others)

    	// Update the permissions
    	if (msgctl(mqid, IPC_SET, &msq_info) == -1) {
        	perror("msgctl");
        	exit(1);
    	}

   
    	printf("Updated Permissions (in octal): %o\n", msq_info.msg_perm.mode);

    	return 0;
}

