#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>

#define KEY (1584)
union semun
{
    int val;
    struct semid_ds *buf;
    ushort * array;
} argument;

int main()
{
    int semid;   /* Number by which the semaphore is known within a program */

    /* The next thing is an argument to the semctl() function. Semctl() 
      does various things to the semaphore depending on which arguments
      are passed. We will use it to make sure that the value of the 
      semaphore is initially 0. */
    
    argument.val = 0;

    /* Create the semaphore with external key KEY if it doesn't already 
      exists. Give permissions to the world. */


    semid = semget(KEY,1, 0666| IPC_CREAT); /// 1 means we waant only 1 semaphore in the set
    if(semid < 0)
    {
        fprintf(stderr, "Unable to obtain semaphore.\n");
        exit(0);
    }

    /* initialize the semaphore */
    int stat = semctl(semid, 0 , SETVAL, argument); 
    
    if(stat<0)
        fprintf(stderr,"failed to initialize semaphore\n");

    else
        fprintf(stderr,"semaphore initialized to %d\n",argument.val);
}
