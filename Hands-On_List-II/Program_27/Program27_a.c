/*
=====================================================================================================================================
Name : Progaram27_a.c
Author : Kuldip Nivruti Bhatale
Roll No : MT2023087
Description :Write a program to receive messages from the message queue.
	     a. with 0 as a flag
	     b. with IPC_NOWAIT as a flag
Date: 10th Oct, 2023.
=====================================================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
	
    	key_t key;
    	int mqid, ret;

    	// Define a structure for the message
    	struct msg {
        	long int m_type;
        	char message[80];
    	} myq;
	
	
	// Generate the key using ftok
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

    	printf("Enter message type: ");
    	scanf("%ld", &myq.m_type);

    	// Receive a message from the queue
    	ret = msgrcv(mqid, &myq, sizeof(myq.message), myq.m_type, 0);

    	if (ret == -1) {
        	perror("msgrcv");
        	exit(1);
    	} else {
        	printf("Message type: %ld\nMessage: %s\n", myq.m_type, myq.message);
    	}

   	 return 0;
}

