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
	//parse right command
	char *args2[50];
	i = 0;
	token = strtok(right, " ");
	while(token){
		args2[i++] = token;
		token = strtok(NULL, " ");
	}
	args2[i] = NULL;

	int P[2];
	if(pipe(P) == -1){
		perror("pipe");
		return;
	}

	// first child (left command)
	if(fork() == 0){
		close(P[0]);              // close read end
		dup2(P[1], 1);            // stdout → pipe
		close(P[1]);              // close original FD
		//Handles Built In commands
		if(strcmp(args1[0],"my_ps")==0){
			my_ps(args1);
			exit(0);
		}
		if(strcmp(args1[0],"my_ls")==0){
			my_ls(args1);
			exit(0);
		}
		if(execvp(args1[0], args1)==-1){
			perror("execvp left");
		}
		exit(1);
	}

	//second child (right command)
	if(fork() == 0){
		close(P[1]);              // close write end
		dup2(P[0], 0);            // stdin ← pipe
		close(P[0]);              // close original FD
		//Handles Built In commands
		if(strcmp(args2[0],"my_ps")==0){
			my_ps(args2);
			exit(0);
		}
		if(strcmp(args2[0],"my_ls")==0){
			my_ls(args2);
			exit(0);
		}
		if(execvp(args2[0], args2)==-1){
			perror("execvp right");
		}
		exit(1);
	}

	// parent
	close(P[0]);
	close(P[1]);

	wait(NULL);
	wait(NULL);
}
