#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) {
        perror("Pipe");
        return 1;
    }

    pid = fork();

    if (pid == -1) {
        perror("Fork");
        return 1;
    }

    if (pid == 0) {
      
        close(fd[0]); // Close read end of the pipe
        dup2(fd[1], STDOUT_FILENO); // Redirect stdout to the pipe

        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(1);
    } else {

        close(fd[1]); // Close write end of the pipe
        dup2(fd[0], STDIN_FILENO); // Redirect stdin to the pipe

        execlp("wc", "wc", NULL);
        perror("execlp");
        exit(1);
    }

    return 0;
}

