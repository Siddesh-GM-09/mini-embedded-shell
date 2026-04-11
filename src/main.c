#include "header.h"
int main(){
	char cmd[1024];
	char* args[100];
	while(1){
		//Prompt
		char cwd[1024];
		char *user = getenv("USER");
		getcwd(cwd, sizeof(cwd));
		char cmd_copy[1024];
		char home[1024];
		snprintf(home, sizeof(home), "/home/%s", user);

		if (strncmp(cwd, home, strlen(home)) == 0){
			printf("\033[1;32m%s@myshell\033[0m:\033[1;34m~%s\033[0m$ ",user, cwd + strlen(home));
		}
		else{
			printf("\033[1;32m%s@myshell\033[0m:\033[1;34m%s\033[0m$ ",user, cwd);
		}
		//Wating for user input
		if(fgets(cmd, sizeof(cmd), stdin) == NULL){
			printf("\n");
			break;
		}
		cmd[strcspn(cmd, "\n")] = 0;  // remove newline
		strcpy(cmd_copy, cmd);
		//Prase into tokens
		memset(args, 0, sizeof(args));
		int i = 0;
		parse_input(cmd,args); //command Parser
		//No Input
		if(args[0] == NULL){
			continue;
		}
		//Built In : cd
		if(strcmp(args[0], "cd") == 0){
			if(args[1] == NULL){
				chdir(getenv("HOME"));
			}
			else if(chdir(args[1]) != 0){
				perror("cd");
			}
			continue;
		}
		//Bulit In : exit
		if(strcmp(args[0], "exit") == 0){
			printf("exiting shell...\n");
			break;
		}
		//input and output redirection Handling 
		if(strchr(cmd_copy,'>') || strchr(cmd_copy,'<')){
			handle_redirection(cmd_copy);
			continue;
		}
		//PIPE Handling
		if(strchr(cmd_copy, '|')){
			handle_pipe(cmd_copy);   // implemented in pipe.c
			continue;
		}
		//my_ls :  mimics the ls
		if(strcmp(args[0], "my_ls") == 0){
			my_ls(args);
			continue;
		}
		//my_ps : mimics the ps 
		if(strcmp(args[0],"my_ps")==0){
			my_ps(args);
			continue;
		}
		//Logs
		logs_file(args);
		//Normal Command Execute
		pid_t pid = fork();
		if(pid == 0){
			execvp(args[0], args);
			perror("exec failed");
			exit(1);
		}
		else{
			wait(NULL);
		}
	}
	return 0;
}
