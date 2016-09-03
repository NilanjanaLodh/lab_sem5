#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

const char* path = "./";
int key_x;
int *xaddr ;
void increment(); // increments the shared variable ... though this function is present in both parent and child, it is executed by child only

void printfac(int childpid);//reads the shared variable, computes factorial and then 
int main(int argc , char ** argv)
{
    key_x = ftok(path,'x');
    int shmid = shmget(key_x, sizeof(int) , 0666 | IPC_CREAT);
    xaddr = (int *)shmat(shmid,NULL, 0);
    /// this  will be shared by all children
    *xaddr = 0 ;

    int n= atoi(argv[1]);// the number of extra processes
    
    int i,mychild;
    
    for(i=0;i<n;i++)
    {
        mychild=fork();
        if(mychild==0)
        {
            increment();
            exit(EXIT_SUCCESS);
        }

        else
        {
            printfac(mychild); // the argument denotes after which of the children the printfac was called
        }
    }
}

void increment()
{
    /// this function will be called only in the child process
    // but since child has all the state exactly copied, the shared memory pointer will be available here 
    // i.e .. we can assume the result of the code lines 1 -> 25 is available to us
    printf("child : %d \n" , getpid());fflush(stdout);
    int x = *xaddr ;
    int dummy=1000 * (getpid()%2);///just to randomize
    printf("    prev x : %d \n", x);fflush(stdout);
    while(dummy--){}
    *xaddr =( x+1);
    printf("    new x : %d \n",*xaddr);fflush(stdout);
    printf("exiting %d\n__________________\n\n", getpid());fflush(stdout);

}

void printfac(int pid)
{
    printf("factorial called due to child no. %d \n",pid);
    int x = *xaddr;
    printf("    current value of x : %d\n", x); fflush(stdout);

    int ans = 1;
    while(x)
    {
        ans*=x;
        x--;
    }

    printf("    factorial computed : %d\n" , ans); fflush(stdout);

    printf("return \n___________________\n\n");fflush(stdout);
}
