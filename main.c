#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "structures.h"
#include "global_vars.h"
#include "prototypes.h"

const int long_size = sizeof(long);
const int int_size = sizeof(int);
int verbose=1;
int target_pid=-1;
unsigned long long target_offset;
int *numbers=NULL;
unsigned long num_numbers;
unsigned long currnum=0;
int quit=0;
int monmode=0;

int main(int argc, char *argv[])
{
    unsigned long long libc_loc;
    unsigned long long mylibc_loc;
    unsigned long long rand_loc;
    int esit;

    esit=parse_cmdline(argc,argv);
    if (esit<=0) {return -2;}
    if (target_pid==-1) {if (verbose>0) {printf(ERROR_NO_PID,argv[0]);}; if (numbers!=NULL) {free(numbers);}; return -1;}

    libc_loc=getOffset(target_pid);
    mylibc_loc=getOffset(getpid());
    rand_loc=nosce_te_ipsum();
    target_offset=rand_loc+4-mylibc_loc+libc_loc;

    if (verbose>0){printf("detected offset: %llX\n",target_offset); fflush(stdout);}

    signal(SIGINT,doquit);

    working_loop();

    free(numbers);
    return 0;
}
