#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    int i;
    int mypid;
    int cpid = fork();
    if(cpid>0)
    {
        mypid = getpid();
        printf("I'm the PARENT ( %d ) and %d is my CHILD \n ",mypid,cpid);
        for(i=0;i<100;i++)
        {
            printf("[%d] parent: %d\n" , mypid , i);
            sleep(1);
        }
    }
    else if(cpid==0)
    {
        mypid=getpid();
        printf("I am %d , the child\n",mypid );
        
        for(i=0;i>-100;i--)
        {
            printf("[%d] child: %d\n" , mypid , i);
        }
    }
}
int main1()
{
    pid_t mypid,cpid;
    
    mypid=getpid();
    printf("CURRENT PROCESS %d\n",mypid);
    
    cpid=fork();
     
    if(cpid>0)
    {
        printf("I'm the PARENT ( %d ) and %d is my CHILD \n ",mypid,cpid);
    }

    if(cpid==0)
    {
        //if you print the old value of mypid here, this will NOT give you the current process id.
        //Rather, this will give you the parent process id because all the values of the child just come preloaded like that from the parent
        int ppid= mypid;// this is the old variable value
        mypid= getpid();
        printf("I am %d , child of %d \n",mypid ,ppid);
    }
}
