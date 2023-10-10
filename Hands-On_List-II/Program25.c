#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

int main() {

    	key_t key;
    	int msgid;
    	struct msqid_ds queue_info;

    	// Generate the key (use the same key you used when creating the message queue)
    	key = ftok(".", 'a');
    	if (key == -1) {
        	perror("ftok");
        	exit(1);
    	}

    	// Get the message queue ID
    	msgid = msgget(key, 0); // Use 0 to retrieve an existing queue
    	if (msgid == -1) {
        	perror("msgget");
        	exit(1);
    	}

    	// Get information about the message queue
    	if (msgctl(msgid, IPC_STAT, &queue_info) == -1) {
        	perror("msgctl");
        	exit(1);
    	}

    	// Print information about the message queue
    	printf("Access Permissions: %o\n", queue_info.msg_perm.mode);
    	printf("UID: %d\n", queue_info.msg_perm.uid);
    	printf("GID: %d\n", queue_info.msg_perm.gid);
    	printf("Time of Last Message Sent: %s", ctime(&queue_info.msg_stime));
    	printf("Time of Last Message Received: %s", ctime(&queue_info.msg_rtime));
    	printf("Time of Last Change: %s", ctime(&queue_info.msg_ctime));
    	printf("Size of Queue: %ld bytes\n", (long)queue_info.msg_qbytes);
    	printf("Number of Messages in Queue: %ld\n", (long)queue_info.msg_qnum);
    	printf("Maximum Number of Bytes Allowed: %ld\n", (long)queue_info.msg_qbytes);
    	printf("PID of msgsnd: %d\n", queue_info.msg_lspid);
    	printf("PID of msgrcv: %d\n", queue_info.msg_lrpid);

    	return 0;


}

