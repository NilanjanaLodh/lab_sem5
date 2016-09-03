
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h> //
#include <sys/shm.h>
#include <sys/sem.h>
#include <semaphore.h> /// used for deallocation

#define flag ( 0666|IPC_CREAT)
const char* path = "./";
int key_x; 
int shmid;
int code_lock;
int semid;


int main()
{
    key_x = ftok(path,'x');
    shmid = shmget(key_x, sizeof(int) , flag);
    shmctl(shmid,IPC_RMID,0);

    code_lock = ftok(path, 'l');
    semid = semget(code_lock,1,flag);

    semctl(semid, -1 , IPC_RMID , 0); /// usually we put the semaphore index in place of -1
}


