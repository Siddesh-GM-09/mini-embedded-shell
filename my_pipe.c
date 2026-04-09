//$ ps -e | grep terminal_no
#include "header.h"
void main(int argc,char** argv){
	if(argc!=2){
		printf("USAGE : my_ps termainal_No\n");
		return;
	}
	int P[2];
	pipe(P);
	perror("Pipe");
	if(fork()==0){            //ps
		close(P[0]);
		dup2(P[1],1);
		execlp("ps","ps","-e",NULL);
	}
	else{
		if(fork()==0){    //grep
			close(P[1]);
			dup2(P[0],0);
			execlp("grep","grep",argv[1],NULL);
		}
		close(P[0]);
		close(P[1]);
		wait(0);
		wait(0);
	}
}

