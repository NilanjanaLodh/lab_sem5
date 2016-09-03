#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define KEY (1584)
int main()
{
    int lockID = semget(KEY,1,0666 | IPC_CREAT);
    struct sembuf wait_op , signal_op;
    wait_op.sem_num = 0; 
    wait_op.sem_op = -1 ;
    wait_op.sem_flg = 0 ;

    signal_op.sem_num = 0 ;
    signal_op.sem_op = 1 ;
    signal_op.sem_flg = 0;

    int mychild=fork();
    /* we've got 2 processes running at this point of time : parent and child 
     * both have access to the semaphore lockID
     * what i want is the parent should go before the child.
     * So.. I will make the child wait on the lock
     * and the parent will go ans open ('signal') the lock.
     * This way, the child can't run until the parent has completed
     **/
   

    if(mychild==0)
    {
        // child process
        printf("I'm the child : waiting for the parent to open the lock\n");fflush(stdout);
        semop(lockID, &wait_op , 1); // 1 is the number of operations
        printf(" child enters\n" );fflush(stdout);
    }
    else
    {
        //parent process
        printf("I'm the parent \n");fflush(stdout);
        semop(lockID,&signal_op, 1);
        printf(" The lock has been opened\n");fflush(stdout);
    }

}
