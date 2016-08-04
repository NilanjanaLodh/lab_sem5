#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
    int i,dummy;
    int pid = getpid();
    int cpid;

    for(i=1;i<argc;i++)
    {
        cpid=fork();
        if(cpid==0)
        {
            char *cmdname= argv[i];
            char* cmdlist[2]={cmdname , NULL};
            execvp(cmdlist[0],cmdlist);

            // the control will reach this place only if execvp fails
            printf("I am the %dth child , but I'm useless because you dont know your commands :P  \n",i);
            break;
        }
        else 
        {
            // parent
            
            wait(&dummy);
        }



    }
}

