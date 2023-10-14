/*
=====================================================================================================================================
Name : Progaram26.c
Author : Kuldip Nivruti Bhatale
Roll No : MT2023087
Description :Write a program to send messages to the message queue. Check $ipcs -q
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
    	int mqid;
    	size_t size;

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

    	// Consume the newline character left in the input buffer
    	while (getchar() != '\n');

    	printf("Enter message text: ");
    	scanf("%[^\n]", myq.message);
    	size = strlen(myq.message);

    	// Send the message to the queue
    	if (msgsnd(mqid, &myq, size + 1, 0) == -1) {
        	perror("msgsnd");
        	exit(1);
    	}

   	 return 0;
}

