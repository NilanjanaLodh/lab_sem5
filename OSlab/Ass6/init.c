#include "common.c"
void init_sema(int key, int val);
void init_shm(int identifier, int val);
int main()
{
    init_sema(KEY1, 1); /// parent -- factorial
    init_sema(KEY2, 0); /// child  -- increment

    init_shm('x', 0);
}
void init_shm(int identifier, int val)
{
    int key_x = ftok("./", identifier);
    int shmid = shmget(key_x , sizeof(int) , 0666|IPC_CREAT);
    if(shmid < 0)
    {
        fprintf(stderr, "Unable to obtain shared memory.\n");
        exit(0);
    }
    int *xaddr = shmat(shmid, 0 , 0);
    if(xaddr<=0)
        fprintf(stderr,"failed to attach shared memory \n");

    else
    {
        xaddr[0] = val;
        fprintf(stderr, "initialized shared memory\n");
    }
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
