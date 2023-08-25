#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
int main(){

	struct{
		int ticket;
	}data;
	data.ticket=1;
	
	int fd = open("ticketInfo.txt", O_RDWR);
	if(fd==-1){
		printf("Failed to open the file \n");
	}

	write(fd, &data, sizeof(data));

	close(fd);

	return 0;
}
