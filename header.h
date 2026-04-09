#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<sys/wait.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<time.h>
#include <fcntl.h>              /* Definition of O_* constants */
#include <unistd.h>
void logs_file(char** );
void list(char *,char *);


