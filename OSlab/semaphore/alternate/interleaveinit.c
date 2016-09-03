#include "interleavecommon.c"
void init_sema(int key, int val);

int main()
{
    init_sema(KEY1, 0); /// parent
    init_sema(KEY2, 1); /// child
}

void init_sema(int key , int val)
{
    union semun argument;
    argument.val = val;
    int semid = semget(key,1, 0666| IPC_CREAT); /// 1 means we waant only 1 semaphore in the set
    if(semid < 0)
    {
        fprintf(stderr, "Unable to obtain semaphore.\n");
        exit(0);
    }
    /* initialize the semaphore */
    int stat = semctl(semid, 0 , SETVAL, argument); /** 0 means the 0th semaphore **/

    if(stat<0)
        fprintf(stderr,"failed to initialize semaphore\n");

    else
        fprintf(stderr,"semaphore initialized to %d\n",argument.val);
}
