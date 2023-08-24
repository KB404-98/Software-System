#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


int main() {

    int fd1 = open("file1.txt", O_CREAT);
    int fd2 = open("file2.txt", O_CREAT);
    int fd3 = open("file3.txt", O_CREAT);
    int fd4 = open("file4.txt", O_CREAT);
    int fd5 = open("file5.txt", O_CREAT);

    printf("%d %d %d %d %d\n", fd1, fd2, fd3, fd4, fd5);
    printf("%d\n", getpid());

    char c = getchar();

    close(fd1);
    close(fd2);
    close(fd3);
    close(fd4);
    close(fd5);

    return 0;

}
