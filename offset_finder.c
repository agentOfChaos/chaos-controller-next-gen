#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "global_vars.h"
#include "prototypes.h"

/*
    used to parse the /proc/PID/maps file,
    looking for libc's offset
*/

unsigned long long readlines(FILE *apri,char *buff)
{
    if (buff==NULL) buff=(char*)malloc(sizeof(char)*MAXLL);
    if (buff==NULL) return 0;

    while (!feof(apri))
        {
        buff[0]='\0';
        fgets(buff,MAXLL,apri);
        if (strstr(buff,LIBCSTR)!=NULL)
            {
            return strtoll(strtok(buff,"-"), NULL, 16);
            }
        }
    return 0;
}

unsigned long long getOffset(pid_t pid)
{
    FILE *mapsfile;
    char path[100];
    char *buff=NULL;
    unsigned long long res;

    snprintf(path,100,"/proc/%d/maps",(int)pid);
    mapsfile=fopen(path,"r");
    if (mapsfile==NULL) return 0;

    res=readlines(mapsfile,buff);
    free(buff);
    fclose(mapsfile);
    return res;
}
