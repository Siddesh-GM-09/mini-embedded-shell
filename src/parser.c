#include "header.h"

void parse_input(char* cmd,char** args){
	int i=0;
	char* token=strtok(cmd," ");
	while(token){
		args[i++]=token;
		token=strtok(NULL," ");
	}
	args[i]=NULL;
}
