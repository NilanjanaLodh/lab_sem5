#include "common.c"
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
     * what i want is the child should go before the parent.
     * So.. I will make the parent wait on the lock
     * and the child will go and open ('signal') the lock.
     * This way, the parent can't run until the parent has completed
     **/
   

    if(mychild>0)
    {
        // parent process
        printf("I'm the parent : waiting for the child to open the lock\n");fflush(stdout);
        semop(lockID, &wait_op , 1); // 1 is the number of operations
        printf(" parent enters\n" );fflush(stdout);
    }
    else
    {
        //child process
        printf("I'm the child \n");fflush(stdout);
        semop(lockID,&signal_op, 1);
        printf(" The lock has been opened\n");fflush(stdout);
    }

    semctl(lockID, 0, IPC_RMID);
}
