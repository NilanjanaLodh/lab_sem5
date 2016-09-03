#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
int killed;
void collect_corpse(int signum)
{
    /// this is the signal handler for sigchild
    int mychild;
    while((mychild = waitpid(-1,0,WNOHANG))>0)
    {
        killed++;
        printf(" collected corpse of %d \n" , mychild); fflush(stdout);fflush(stdout);
    }
}
int main()
{
    killed=0;
    //signal(SIGCHLD, collect_corpse);
    int mychild;
    int i;
    for(i=0;i<10;i++)
    {
        mychild=fork();
        if(mychild==0)
        {
            int x=100;
            while(x--){}//just introducing delay
            printf("        I' m dyin (%d , %d)\n", i, getpid()); fflush(stdout);
            exit(0);
        }
    }
    /// all the children will have been created at this point
    // some may have even died by now ( and have become zombies)
    // and some are still running ..

    //since WNOHANG has not been specified , in this case wait acts like blocking system call
    // that is, once wait() is called , the parent process is totally freezed until a child terminates
    // in the mean time, the child processes can continue running
    // if there are zombie children(that is the child has already terminated ), the wait return
    //printf("killed %d so far\n", killed);fflush(stdout);
     
    while((mychild = waitpid(-1,0,0))!=-1)
        printf(" parent : collected corpse of %d \n" , mychild); fflush(stdout);


    /// by this time , all children will have finished running and their corpses will have been collected
    printf("exiting parent\n");fflush(stdout);
}

