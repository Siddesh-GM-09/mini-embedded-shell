//Custom ps command 
#include "header.h"
void my_ps(char** args){
	// $ ps
	if(args[1]==NULL){  
		if(fork()==0){
			if(execlp("ps", "ps", NULL)==-1){
				perror("execlp");
			}
		}
		wait(NULL);
		return;
	}
	// $ ps -e
	if(strcmp(args[1],"-e")==0){
		if(fork()==0){
			if(execlp("ps","ps","-e",NULL)==-1){
				perror("execlp");
			}
		}
		wait(NULL);
		return;
	}
	printf("Usage: my_ps or my_ps -e\n");
}
