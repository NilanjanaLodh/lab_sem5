#include "common.c"
struct sembuf wait_op ={ 0 , -1 ,0 };
struct sembuf signal_op= {0, 1 , 0};
int main()
{
    int mychild, lockID = semget(KEY, 1 , 0666|IPC_CREAT);
    mychild= fork();
    if(mychild==0)
    {
        /*child*/
        semop(lockID, &wait_op , 1);
        printf("             child\n");fflush(stdout);
    }
    else
    {
        /*parent*/
        printf("parent opening lock ...\n");
        semop(lockID, &signal_op , 1);
    }

    semctl(lockID,0,IPC_RMID);
}
