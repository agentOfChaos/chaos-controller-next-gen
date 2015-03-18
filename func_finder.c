#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/stat.h>
#include "structures.h"
#include "global_vars.h"
#include "prototypes.h"

unsigned long long int nosce_te_ipsum() // get a pointer to the rand() function in libc
{
    void *altro;
    altro=dlsym(RTLD_NEXT,"rand");
    return (unsigned long long int)altro;
}
