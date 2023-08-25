

#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>


int main(){

	struct flock lock;
	int fd;
	fd = open("db", O_RDWR);
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_pid = getpid();

	printf("Before entering into Critical Section \n");

	fcntl(fd, F_SETLKW, &lock);
	printf("Inside the Critical Section... \n");
	printf("Enter to unlock.. \n");
	getchar();
	printf("Unlocked\n");

	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);

	printf("Finish\n");
	return 0;
}
