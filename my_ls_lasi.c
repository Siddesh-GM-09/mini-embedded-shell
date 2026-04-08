#include "header.h"
void main(int argc, char **argv)
{
	if(argc==1)
		list(".",NULL);
	else if(argc==2)
	{
		if(argv[1][0]!='-')
			list(argv[1],NULL);
		else
			list(".",argv[1]+1);
	}
	else if(argc==3)
	{
		if(argv[1][0]=='-')
			list(argv[2],argv[1]+1);
		else if(argv[2][0]=='-')
			list(argv[1],argv[2]+1);
	}
}
void list(char *fpath,char *mode){
	printf("in function %s %s\n",fpath,mode);
	struct stat v;
	struct dirent *p;
	DIR *dp;
	char path[100];
	char time[50];
	int i;
	dp=opendir(fpath);
	if(dp==0)
	{
		perror("opendir");
		return;
	}
	while(p=readdir(dp))
	{
		if(mode==NULL||strlen(mode)==1&&strchr(mode,'a'))
		{
			strcpy(path,fpath);
			if(mode&&(strlen(mode)==1)&&strchr(mode,'a'))
				printf("%s\t",p->d_name);
			else
				{
					if(p->d_name[0]!='.')
						printf("%s\t",p->d_name);
				}
		}
		else
		{
			strcpy(path,fpath);
			strcat(path,"/");
			strcat(path,p->d_name);
		}
		stat(path,&v);
		if(mode)
		{
			if(strchr(mode,'a') || p->d_name[0]!='.')
			{
				if(strchr(mode,'i'))
					printf("%-5u ",(unsigned int)p->d_ino);
				if(strchr(mode,'s'))
					printf("%2d ",(int)v.st_blocks/2);
				if(strchr(mode,'l'))
				{
					/*DT_DIR*/
					if(p->d_type==4)printf("d");
					/*DT_REG*/
					else if(p->d_type==8)printf("-");
					/*DT_LNK*/
					else if(p->d_type==10)printf("l");
					else if(p->d_type==DT_FIFO)printf("p");
					else if(p->d_type==DT_SOCK)printf("s");
					else if(p->d_type==DT_CHR)printf("c");
					else if(p->d_type==DT_BLK)printf("b");
					else printf(" ");
					print((int)v.st_mode);
					printf(" ");
					printf("%2d ",(int)v.st_nlink);
					printf("%5u ",(unsigned int)v.st_uid);
					printf("%5u ",(unsigned int)v.st_gid);
					printf("%5d ",(int)v.st_size);
					strcpy(time,ctime(&v.st_mtime));
					for(i=0;time[i];i++);
					time[i-9]=time[i];
					printf("%-10s ",time+4);
					printf("%-5s\n",p->d_name);
				}
			}//-a check
		}//end of if(mode)
	}//end while
	printf("\n");
}
////print()////
void print(int n)
{
	int i;
	for(i=8;i>=0;i--)
	{
		if(i==8||i==5||i==2)
		{
			if(n&1<<i)
				printf("r");
			else
				printf("-");
		}
		if(i==7||i==4||i==1)
		{
			if(n&1<<i)
				printf("w");
			else
				printf("-");
		}
		if(i==6||i==3||i==0)
		{
			if(n&1<<i)
				printf("x");
			else
				printf("-");
		}
	}
}
