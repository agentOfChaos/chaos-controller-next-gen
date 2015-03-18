#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/user.h>
#include "structures.h"
#include "global_vars.h"
#include "prototypes.h"

void detach(pid_t pid)
{
    ptrace(PTRACE_DETACH,pid,NULL,NULL);
}
void pause_pid(pid_t pid)
{
    ptrace(PTRACE_INTERRUPT,pid,NULL,NULL);
}
int attach_n_stop(pid_t pid)
{
    int ret;
    ret=ptrace(PTRACE_SEIZE,pid,NULL,NULL);
    if (ret!=-1)
        {
        pause_pid(pid);
        wait(NULL);
        }
    return ret;
}
void target_go_on(pid_t pid)
{
    ptrace(PTRACE_CONT, pid, NULL, NULL);
}
void read_registers(pid_t pid, struct user_regs_struct *regs)
{
    ptrace(PTRACE_GETREGS,pid,NULL,regs);
}
void write_registers(pid_t pid, struct user_regs_struct *regs)
{
    ptrace(PTRACE_SETREGS,pid,NULL,regs);
}
