#include "header.h"
void logs_file(char** cmd){
	int fd=open(".log.txt",O_RDWR|O_CREAT|O_APPEND,0664);
	if(fd<0){
		perror("Open");
		return;
	}
	register int i=0;
	while(cmd[i]!=NULL){
		write(fd,cmd[i],strlen(cmd[i]));
		write(fd," ",1);
		i++;
	}
	write(fd,"\n",1);
	close(fd);
}
