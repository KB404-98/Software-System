
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <errno.h>


int main(){

	int fd[2];

	char buff[10];

	if(pipe(fd)==-1){

		perror("Pipe");
		exit(1);
	}

	write(fd[1],"Kuldip",7);

	read(fd[0], buff, 7);

	printf("%s\n",buff);


}
