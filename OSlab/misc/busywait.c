#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
int main()
{
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
    while((mychild = waitpid(-1,0,WNOHANG))!=-1)
    printf(" collected corpse of %d \n" , mychild); fflush(stdout);

    /// by this time , all children will have finished running and their corpses will have been collected
    printf("exiting parent\n");
}
