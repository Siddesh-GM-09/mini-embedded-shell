//$ ps -e | grep terminal_no
#include "header.h"
void handle_pipe(char *cmd){
	char *left = strtok(cmd, "|");
	char *right = strtok(NULL, "|");
	if(left == NULL || right == NULL){
		printf("Invalid pipe command\n");
		return;
	}
	// parse left command
	char *args1[50];
	int i = 0;
	char *token = strtok(left, " ");
	while(token){
		args1[i++] = token;
		token = strtok(NULL, " ");
	}
	args1[i] = NULL;
	// 🔹 parse right command
	char *args2[50];
	i = 0;
	token = strtok(right, " ");
	while(token){
		args2[i++] = token;
		token = strtok(NULL, " ");
	}
	args2[i] = NULL;

	int P[2];
	if(pipe(P)==-1){
		perror("Pipe");
		exit(1);
	}
	char *pipe_pos = strchr(cmd, '|');
	//first child,left command
	if(fork()==0){            
		close(P[0]);
		dup2(P[1],1);
		execvp(args1[0],args1);
		perror("execvp left");
		exit(1);
	}
	//second child,right command
	if(fork()==0){    
		close(P[1]);
		dup2(P[0],0);
		execvp(args2[0],args2);
		perror("execvp right");
		exit(1);
	}
	close(P[0]);
	close(P[1]);
	wait(NULL);
	wait(NULL);
}

