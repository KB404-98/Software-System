/*
=================================================================================
Name : Program27.c
Author : Kuldip Nivruti Bhatale
Roll No : MT2023087
Description : Write a program to execute ls -Rl by the following system calls
 a. execl
 b. execlp
 c. execle
 d. execv
 e. execvp
Date: 8th Sep, 2023.
=================================================================================
*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> // Include string.h for strcmp

int main() {
    printf("\nExecuting 'ls -rl' command by using exec family of functions \n");

    printf("\n----Menu----\n a.execl\n b.execlp\n c.execle\n d.execv\n e.execvp\n\n");
    char c;
    printf("Enter Choice :\n");
    scanf(" %c", &c); // Add a space before %c to consume leading whitespace

    int i;

    switch (c) {
        case 'a':
            i = execl("/usr/bin/ls", "ls", "-rl", NULL);
            if (i == -1) {
                perror("execl");
                exit(EXIT_FAILURE);
            }
            break;

        case 'b':
            i = execlp("ls", "ls", "-rl", NULL);
            if (i == -1) {
                perror("execlp");
                exit(EXIT_FAILURE);
            }
            break;

        case 'c': {
            const char *command = "/bin/ls";
            const char *arg0 = "ls";
            const char *arg1 = "-rl";
            const char *args[] = {arg0, arg1, NULL};

            char *env[] = {"PATH=/bin:/usr/bin", NULL};

            i = execle(command, arg0, arg1, NULL, env);
            if (i == -1) {
                perror("execle");
                exit(EXIT_FAILURE);
            }
            break;
        }

        case 'd': {
            const char *command = "/bin/ls";
            const char *arg0 = "ls";
            const char *arg1 = "-rl";
            const char *args[] = {command, arg0, arg1, NULL};

            i = execv(command, (char *const *)args);
            if (i == -1) {
                perror("execv");
                exit(EXIT_FAILURE);
            }
            break;
        }

        case 'e': {
            const char *command = "ls";
            const char *arg0 = "ls";
            const char *arg1 = "-rl";
            const char *args[] = {command, arg0, arg1, NULL};

            i = execvp(command, (char *const *)args);
            if (i == -1) {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
            break;
        }

        default:
            printf("Wrong choice\n");
            break;
    }

    printf("This code will never be executed\n");

    return 0;
}

