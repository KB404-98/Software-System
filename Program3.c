

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

int main(){

	int fd = creat("temp1.txt", S_IRUSR | S_IWUSR);

	if(fd == -1){
	
		printf("Error No is : %d \n", errno);
		perror("Error");
		return 1;
	}

	printf("File Created Successfully \n");

	printf("File Descriptor Value is : %d \n", fd);

	close(fd);


	return 0;
}
