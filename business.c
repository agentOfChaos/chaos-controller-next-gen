#include <stdio.h>
#include <stdlib.h>
#include <sys/user.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "structures.h"
#include "global_vars.h"
#include "prototypes.h"

char backup_0[14];

void printbytes(char *b,int len)
{
    int cont;
    for (cont=0; cont<len; cont++)
        {
        if (cont+1<len)printf("%02X ",(unsigned)(unsigned char)b[cont]);
        else printf("%02X",(unsigned)(unsigned char)b[cont]);
        }
}

/*inline void working_step(struct user_regs_struct *regs)
{
    char backup[7];
    char sonda[25];
    char inject_mov[50];
    long long int *ip=&(regs->rip);
    char breakpoint[]={0xcd,0x80,0xcc,0x90,0x90};
    poison inject_param;

    inject_mov[0]=MOV_OPCODE;
    inject_param.val=numbers[currnum];
    memcpy(inject_mov+1,inject_param.chars,4);
    memcpy(inject_mov+5,breakpoint,4);//
    currnum++;
    currnum=currnum%num_numbers;

    wait(NULL);
    read_registers(target_pid,regs);
    if (verbose>1){printf("> phase 1: rip %llX->%llX\n",*ip,target_offset); fflush(stdout);}
    (*ip)=target_offset;
    opera_mem(target_pid,LEGGI,target_offset+5,backup,4); // backup next instruction
    opera_mem(target_pid,SCRIVI,target_offset,inject_mov,9); // inject num assignation
    if (verbose>1){printf("> next bp: %llX\n",(*ip)+5); fflush(stdout);}
    //opera_mem(target_pid,SCRIVI,target_offset+5,breakpoint,4); // inject next breakpoint
    write_registers(target_pid,regs); // restore registers

    if (verbose>1)
        {
        opera_mem(target_pid,LEGGI,target_offset,sonda,9);
        printf("injected value(s): ");
        printbytes(sonda,9);
        printf("\n");
        printf("backed up original instruction: ");
        printbytes(backup,4);
        printf("\n");
        fflush(stdout);
        }
    target_go_on(target_pid); quit=1;
    wait(NULL);

    read_registers(target_pid,regs);
    if (verbose>1){printf(">> test rax: %llX\n",regs->rax); fflush(stdout);}
    if (verbose>1){printf(">> phase 2: rip %llX->%llX\n",*ip,(*ip)-3); fflush(stdout);}
    (*ip)-=3;
    memcpy(inject_mov,breakpoint,5);
    memcpy(inject_mov+5,backup,4);
    opera_mem(target_pid,SCRIVI,target_offset,inject_mov,9); // restore current instruction
    if (verbose>1)
        {
        opera_mem(target_pid,LEGGI,(*ip),sonda,5);
        printf("restored value: ");
        printbytes(sonda,5);
        printf("\n");
        fflush(stdout);
        }
    //opera_mem(target_pid,SCRIVI,target_offset,breakpoint,5); // re-create first breakpoint

    if (verbose>1)
        {
        opera_mem(target_pid,LEGGI,(*ip)-5,sonda,9);
        printf("injected value(s): ");
        printbytes(sonda,9);
        printf("\n");
        }

    write_registers(target_pid,regs); // restore registers
    if (verbose>1){printf("\n"); fflush(stdout);}
    getchar();

    target_go_on(target_pid);
}*/
void working_step(struct user_regs_struct *regs)
{
    char backup[7];
    char sonda[50];
    char inject_mov[50];
    int status,estrai;
    poison inject_param;

    inject_mov[0]=MOV_OPCODE;
    if (monmode)
        {
        estrai=rand();
        inject_param.val=estrai;
        }
    else
        {
        inject_param.val=numbers[currnum];
        currnum++;
        currnum=currnum%num_numbers;
        }
    memcpy(inject_mov+1,inject_param.chars,4);

    waitpid(target_pid,&status,0);
    if (WIFEXITED(status))
        {
        if (verbose>0)printf("Target %d died. How evil.\n",target_pid);
        quit=1;
        }
    else
        {
        opera_mem(target_pid,SCRIVI,target_offset,inject_mov,5); // inject num assignation
        opera_mem(target_pid,LEGGI,target_offset-4,sonda,15);
        if (verbose>1)
            {
            printf("Dump istruzioni: ");
            printbytes(sonda,15);
            if (monmode)
                {
                printf(" number: %d",estrai);
                }
            printf("\n");
            fflush(stdout);
            //getchar();
            }
        target_go_on(target_pid);
        }
}
void doquit(int signum)
{
    if (!quit)
        {
        printf(" Caught termination signal. Waiting for graceful termination.\n");
        quit=1;
        }
    else
        {
        printf(" Forcing termination.\n");
        pause_pid(target_pid);
        opera_mem(target_pid,SCRIVI,target_offset-4,backup_0,14); // restore call instruction
        target_go_on(target_pid);
        detach(target_pid);
        exit(0);
        }
}
int working_loop()
{
    char sonda[30];
    char breakpoint[]={0xcd,0x80,0xcc,0x90,0x90};
    char noppad[]={0x90,0x90,0x90,0x90};
    struct user_regs_struct regs;
    if(attach_n_stop(target_pid)==-1) return -1;
    if (verbose>0) {printf("Success attaching %d\n",target_pid); fflush(stdout);}
    opera_mem(target_pid,LEGGI,target_offset-4,backup_0,14); // backup call instruction
    if (verbose>1)
        {
        printf("backed up original 'callq': ");
        printbytes(backup_0,14);
        printf("\n");
        fflush(stdout);
        }
    opera_mem(target_pid,SCRIVI,target_offset-4,breakpoint,4); // create first breakpoint
    opera_mem(target_pid,SCRIVI,target_offset+5,noppad,4);
    if (verbose>1)
        {
        opera_mem(target_pid,LEGGI,target_offset-4,sonda,14);
        printf("new value: ");
        printbytes(sonda,14);
        printf("\n");
        fflush(stdout);
        }
    target_go_on(target_pid); // run target process
    if (verbose>1) {printf("Resuming %d\n",target_pid); fflush(stdout);}
    while (!quit)
        {
        working_step(&regs);
        }
    wait(NULL);
    read_registers(target_pid,&regs);
    #ifdef MACHINE64
    regs.rip=target_offset-4;
    #else
    regs.eip=target_offset-4;
    #endif
    write_registers(target_pid,&regs);
    //pause_pid(target_pid);
    opera_mem(target_pid,SCRIVI,target_offset-4,backup_0,14); // restore call instruction
    if (verbose>1)
        {
        opera_mem(target_pid,LEGGI,target_offset-4,sonda,14);
        printf("restored: ");
        printbytes(sonda,14);
        printf("\n");
        fflush(stdout);
        }
    target_go_on(target_pid);
    detach(target_pid);
    return 1;
}
