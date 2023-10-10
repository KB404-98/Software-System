#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {

   	 key_t key;
   	 int msgid;

    	// Generate a unique key using ftok
    	key = ftok(".", 'a');
    	if (key == -1) {
        	perror("ftok");
	       	exit(1);
    	}

   	 // Create a message queue
   	 msgid = msgget(key, IPC_CREAT | IPC_EXCL | 0644);
   	 if (msgid == -1) {
        	perror("msgget");
        	exit(1);
    	}

   	 // Print the key and message queue ID
   	 printf("Key: 0x%08x\n", key);
   	 printf("Message Queue ID: %d\n", msgid);

   	 return 0;
}

