
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>



int main()
{

	int fd = open("Existing_File", O_RDWR | O_EXCL);


	if (fd == -1) {
		
		printf("Error No : %d \n",errno);	
		
		perror("Error");

		return 1;
	}

	printf("File opened successfully.\n");

	close(fd);

	
	return 0;
}

