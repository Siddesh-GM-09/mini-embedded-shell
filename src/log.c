#include "header.h"
void logs_file(char** cmd){
	FILE* fp=fopen(".log.txt","a+");
	register int i=0;
	while(cmd[i]!=NULL){
		fprintf(fp,"%s ",cmd[i]);
		i++;
	}
	fprintf(fp,"\n");
	fclose(fp);
	fp=NULL;
}
