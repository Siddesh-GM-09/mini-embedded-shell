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
#include <fcntl.h>           
#include <unistd.h>
void logs_file(char** );
void handle_pipe(char*);
void my_ls(char **args);
void list(char *fpath, char *mode);
void print(int n);
void handle_redirection(char *);
void my_ps(char**);
void parse_input(char*,char**);
