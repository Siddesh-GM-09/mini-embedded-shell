#include "header.h"
volatile int flag=1;
int main(){
	char* cmd=malloc(sizeof(char)*1024);
	char* args[100];
	while(1){
		if(flag){
			printf("myshell>");
			scanf(" %[^\n]",cmd);
			flag=0;
			int i=0;
			char* token=strtok(cmd," ");
			while(token!=NULL){
				args[i++]=token;
				token=strtok(NULL," ");
			}
			args[i]=NULL;
		}
		if(args[0]==NULL){
			continue;
		}
		logs_file(args);
		if(strcmp(args[0],"exit")==0){
			printf("exiting shell...\n");
			return 0;
		}
		if(!flag){
			if(fork()==0){
				execvp(args[0],args);
				perror("execlp failed");
				exit(1);
			}
			if(wait(0)!=-1){
				flag=1;
			}
		}
	}
	free(cmd);
	cmd=NULL;
	return 0;
}
