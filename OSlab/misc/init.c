#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h> //
#include <sys/shm.h>
#include <sys/sem.h>
#include <semaphore.h> /// used for deallocation
#define flag ( 0666)
#define LOCK 0
const char* path = "./";
int key_x; 
int shmid;
union semun 
{
    int val;
    struct semid_ds *buf;
    int *arr;
};
int code_lock;
int semid;


int main()
{
    key_x = ftok(path,'x');
    shmid = shmget(key_x, sizeof(int) , flag);

    code_lock = ftok(path, 'l');
    semid = semget(code_lock,1,flag);

    union semun arg;
    arg.arr=(int*)(malloc(sizeof(int)*1));
    arg.arr[0]=0;///locked state
    semctl(semid, -1 , SETALL , &arg); /// usually we put the semaphore index in place of -1
}


