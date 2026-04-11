#include "header.h"

// main function for shell
void my_ls(char **args)
{
    int argc = 0;
    while(args[argc] != NULL)
        argc++;

    if(argc == 1)
        list(".", NULL);

    else if(argc == 2)
    {
        if(args[1][0] != '-')
            list(args[1], NULL);
        else
            list(".", args[1] + 1);
    }

    else if(argc == 3)
    {
        if(args[1][0] == '-')
            list(args[2], args[1] + 1);
        else if(args[2][0] == '-')
            list(args[1], args[2] + 1);
    }
}

// list function
void list(char *fpath, char *mode)
{
    struct stat v;
    struct dirent *p;
    DIR *dp;
    char path[256];
    char timebuf[64];

    dp = opendir(fpath);
    if(dp == NULL){
        perror("opendir");
        return;
    }

    while((p = readdir(dp)) != NULL)
    {
        // build full path
        snprintf(path, sizeof(path), "%s/%s", fpath, p->d_name);

        if(stat(path, &v) == -1){
            perror("stat");
            continue;
        }

        // skip hidden files unless -a
        if(!mode || !strchr(mode, 'a')){
            if(p->d_name[0] == '.')
                continue;
        }

        //  inode
        if(mode && strchr(mode, 'i'))
            printf("%-6lu ", (unsigned long)p->d_ino);

        //  blocks
        if(mode && strchr(mode, 's'))
            printf("%4ld ", (long)v.st_blocks/2);

        //  long listing
        if(mode && strchr(mode, 'l'))
        {
            // file type
            if(S_ISDIR(v.st_mode)) printf("d");
            else if(S_ISLNK(v.st_mode)) printf("l");
            else printf("-");

            // permissions
            print(v.st_mode);
            printf(" ");

            printf("%2lu ", (unsigned long)v.st_nlink);
            printf("%5u ", v.st_uid);
            printf("%5u ", v.st_gid);
            printf("%6ld ", (long)v.st_size);

            // time
            strncpy(timebuf, ctime(&v.st_mtime), sizeof(timebuf));
            timebuf[strlen(timebuf)-1] = '\0'; // remove newline
            printf("%.12s ", timebuf + 4);
        }

        printf("%s\n", p->d_name);
    }

    closedir(dp);
}

// permission printer
void print(int n)
{
    for(int i = 8; i >= 0; i--)
    {
        if(i%3 == 2)
            printf((n & (1<<i)) ? "r" : "-");
        else if(i%3 == 1)
            printf((n & (1<<i)) ? "w" : "-");
        else
            printf((n & (1<<i)) ? "x" : "-");
    }
}
