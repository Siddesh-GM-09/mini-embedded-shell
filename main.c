#include "header.h"
volatile int flag=1;
int main(){
	char* cmd=malloc(sizeof(char)*1024);
	char* args[100];
	while(1){
		if(flag){
			char cwd[1024];
			char *user = getenv("USER");

			getcwd(cwd, sizeof(cwd));

			char home[1024];
			snprintf(home, sizeof(home), "/home/%s", user);

			if (strncmp(cwd, home, strlen(home)) == 0){
				printf("\033[1;32m%s@myshell\033[0m:\033[1;34m~%s\033[0m$ ",user, cwd + strlen(home));
			} 
			else{
				printf("\033[1;32m%s@myshell\033[0m:\033[1;34m%s\033[0m$ ",user, cwd);
			}
			fgets(cmd,1024, stdin);
			cmd[strcspn(cmd, "\n")] = 0;
			memset(args, 0, sizeof(args));
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
		if(strcmp(args[0], "cd") == 0){
			if(args[1] == NULL){
				if(chdir(getenv("HOME")) != 0)
					perror("cd");
			}
			else{
				if(chdir(args[1]) != 0)
					perror("cd");
			}
			flag=1;
			continue;
		}
		/*if(strcmp(args[0],"cd")==0){
			if(args[1]==NULL){
				chdir(getenv("HOME"));
			}
			else{
				chdir(args[1]);
			}
			continue;
		}*/
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
