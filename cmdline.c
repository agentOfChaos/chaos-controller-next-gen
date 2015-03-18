#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "global_vars.h"
#include "prototypes.h"

void print_help(char *pname)
{
    printf("Chaos controller next-gen  by agentOfChaos  informaniac99<AT>gmail<DOT>com\n\n");
    printf("Usage: %s -p [target pid] [list of space-separated numbers]...\n\n",pname);
    printf("When the program is launched (with proper permissions), it will attempt to\n");
    printf("attach the target pid and set a breakpoint in its code (just like debuggers do).\n");
    printf("Now, every time the target calls rand(), the function will return the numbers\n");
    printf("chosen by you (instad of random ones), isn't that cool?\n");
    printf("The numbers will be returned in order with each subsequent call, the list will\n");
    printf("be looped over if needed.\n\n");
    printf("options:\n");
    printf("-h  --help\t\tShow this message. Duh.\n");
    printf("-m  --monitor\t\tInject actual random values, echoing them on screen.\n");
    printf("-p  --pid\t\t[mandatory] target process'id.\n");
    printf("-s  --silent\t\tDo not print status messages.\n");
    printf("-v  --verbose\t\tEnables verbose mode.\n");

}

int opt_verb(char *opt)
{
    if (strcmp(opt,"-s")==0) return 1;
    if (strcmp(opt,"--silent")==0) return 1;
    return 0;
}
int opt_vverb(char *opt)
{
    if (strcmp(opt,"-v")==0) return 1;
    if (strcmp(opt,"--verbose")==0) return 1;
    return 0;
}
int opt_pid(char *opt)
{
    if (strcmp(opt,"-p")==0) return 1;
    if (strcmp(opt,"--pid")==0) return 1;
    return 0;
}
int opt_mon(char *opt)
{
    if (strcmp(opt,"-m")==0) return 1;
    if (strcmp(opt,"--monitor")==0) return 1;
    return 0;
}
int opt_help(char *opt)
{
    if (strcmp(opt,"-h")==0) return 1;
    if (strcmp(opt,"--help")==0) return 1;
    return 0;
}
int parse_cmdline(int argc, char *argv[])
{
    int cont;
    int startnum=argc;

    for (cont=1; cont<argc; cont++)
        {
        if (opt_verb(argv[cont]))
            {
            verbose=0;
            }
        else if (opt_vverb(argv[cont]))
            {
            verbose=2;
            }
        else if (opt_mon(argv[cont]))
            {
            monmode=1;
            }
        else if (opt_help(argv[cont]))
            {
            print_help(argv[0]);
            exit(0);
            }
        else if (opt_pid(argv[cont]) && argv[cont+1]!=NULL)
            {
            target_pid=atoi(argv[cont+1]);
            cont++;
            }
        else
            {
            startnum=cont;
            break;
            }
        }

    num_numbers=argc-startnum;
    if (num_numbers<=0 && !monmode) return -1;

    numbers=(int*)malloc(sizeof(int)*abs(num_numbers));
    if (numbers==NULL) return 0;
    for (cont=0; cont<num_numbers; cont++)
        {
        numbers[cont]=atoi(argv[startnum+cont]);
        }
    return 1;
}
