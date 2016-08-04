#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>


int main(int argc, char** argv)
{
    int c;
    pid_t pid = getpid(); //get current process id
    
    printf("PID of current process is %d\n",pid);

    c=fgetc(stdin);

    exit(0);
}

