#include "header.h"

void handle_redirection(char *cmd){
	char *args[50];
	char *file;
	int fd;
	//Output redirection >
	if(strchr(cmd,'>')){
		int i=0;
		char* left=strtok(cmd,">");
		char* right=strtok(NULL,">");
		if(left==NULL || right==NULL){
			printf("Invalid Output Redirection\n");
			return;
		}
		file=strtok(right," \n");
		char* token=strtok(left," ");
		while(token){
			args[i++]=token;
			token=strtok(NULL," ");
		}
		args[i]=NULL;
		if(fork()==0){
			fd=open(file,O_WRONLY|O_CREAT|O_TRUNC,0664);
			dup2(fd,1);//redirect to stdout -> 1
			close(fd);
			execvp(args[0],args);
			perror("execvp");
			exit(1);
		}
		wait(NULL); 
	}
	else if(strchr(cmd,'<')){     //Input redirection <
		int i=0;
		char* left=strtok(cmd,"<");
		char* right=strtok(NULL,"<");
		if(left==NULL || right==NULL){
			printf("Invalid Input Redirection\n");
			return;
		}
		file=strtok(right," \n");
		char* token=strtok(left," ");
		while(token){
			args[i++]=token;
			token=strtok(NULL," ");
		}
		args[i]=NULL;
		if(fork()==0){
			fd=open(file,O_RDONLY);
			dup2(fd,0);//redirect to stdin -> 0
			close(fd);
			execvp(args[0],args);
			perror("execvp");
			exit(1);
		}
		wait(NULL);
	}
}
