#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/user.h>
#include <errno.h>
#include <signal.h>
#include <linux/limits.h>
#include "structures.h"
#include "global_vars.h"
#include "prototypes.h"

void getdata(pid_t child, long addr,char *str, int len) // those two 'sister' functions used to work on the memory aren't mine, but borrowed from an article on linuxjournal. Open source is like this. Yap.
{
    char *laddr;
    int i, j;
    union u {
            long val;
            char chars[long_size];
    }data;
    i = 0;
    j = len / long_size;
    laddr = str;
    while(i < j) {
        data.val = ptrace(PTRACE_PEEKDATA, child,
                          addr + i * 4, NULL);
        memcpy(laddr, data.chars, long_size);
        ++i;
        laddr += long_size;
    }
    j = len % long_size;
    if(j != 0) {
        data.val = ptrace(PTRACE_PEEKDATA, child,
                          addr + i * 4, NULL);
        memcpy(laddr, data.chars, j);
    }
    str[len] = '\0';
}
void putdata(pid_t child, long addr,char *str, int len)
{
    char *laddr;
    int i, j;
    union u {
            long val;
            char chars[long_size];
    }data;
    i = 0;
    j = len / long_size;
    laddr = str;
    while(i < j) {
        memcpy(data.chars, laddr, long_size);
        ptrace(PTRACE_POKEDATA, child,
               addr + i * 4, data.val);
        ++i;
        laddr += long_size;
    }
    j = len % long_size;
    if(j != 0) {
        memcpy(data.chars, laddr, j);
        ptrace(PTRACE_POKEDATA, child,
               addr + i * 4, data.val);
    }
}
int opera_mem(pid_t target, int mode, long addr, unsigned char *bytes, int numbytes)
{
    unsigned char buff[16];
    long cont,endpadd,startcopy;

    if (mode==SCRIVI)
        {
        startcopy=(numbytes/DATAWORD)*DATAWORD; // arrotonda a 8
        endpadd=(numbytes%DATAWORD == 0 ? startcopy : startcopy+DATAWORD); // arrotonda a 8 per eccesso
        //printf("addr startcopy endpadd = %ld %ld %ld\n",addr,startcopy,endpadd); fflush(stdout);

        getdata(target, addr+startcopy, buff, DATAWORD); // workaround for ptrace writing only blocks of 8 bytes
        for (cont=0; cont<numbytes%DATAWORD; cont++)
            {
            buff[cont]=bytes[startcopy+cont];
            }
        //printf("\n> "); printbytes(buff,8); printf("\n");
        //printf("addr startcopy endpadd = %ld %ld %ld %ld\n",addr,startcopy,endpadd,cont); fflush(stdout);
        for (cont=0; cont<endpadd/DATAWORD; cont++) // writes 8 byte blocks per cycle
            {
            if (cont==(startcopy/DATAWORD)){putdata(target,(cont*DATAWORD)+addr,buff,DATAWORD);}
            else {putdata(target,(cont*DATAWORD)+addr,bytes+(cont*DATAWORD),DATAWORD);}
            }
        return 1;
        }
    else
        {
        if (bytes==NULL)
            {
            bytes=(unsigned char*)malloc(sizeof(char)*numbytes);
            if (bytes==NULL) return 0;
            }
        for (cont=0; cont<(numbytes%DATAWORD == 0 ? numbytes/DATAWORD : (numbytes/DATAWORD)+1); cont++)
            {
            getdata(target, addr+(cont*DATAWORD), buff, DATAWORD);
            if (cont>numbytes)memcpy(bytes+(cont*DATAWORD),buff,(numbytes%DATAWORD));
            else memcpy(bytes+(cont*DATAWORD),buff,DATAWORD);
            }
        return 1;
        }
}
