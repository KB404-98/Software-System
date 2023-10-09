
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {

    const char *filename = "myfifo2";

    // Create the FIFO with read and write permissions
    if (mkfifo(filename, 0666) == -1) {

        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    printf("FIFO file '%s' created successfully.\n", filename);

    return 0;
}

