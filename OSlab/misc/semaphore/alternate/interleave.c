#include "interleavecommon.c"

int main()
{
    int lockparent = semget(KEY1, 1 , 0666|IPC_CREAT);
    int lockchild  = semget(KEY2, 1 , 0666|IPC_CREAT);

    int mychild= fork();
    if(mychild==0)
    {
        int x= 10;
        int c,p;
        while(x--)
        {
            semop(lockchild,&wait_op, 1);
//            c = semctl(lockchild,0,GETVAL);
//            p = semctl(lockparent,0,GETVAL);
//            printf("lockchild semaphore value %d\n" , c);fflush(stdout);
//            printf("lockparent semaphore value %d\n" , p);fflush(stdout);
            printf("child \n");fflush(stdout);
            semop(lockparent,&signal_op, 1);

        }
    }
    else
    {
        int x = 10;
        while(x--)
        {

            semop(lockparent , &wait_op , 1);
//            int c = semctl(lockchild,0,GETVAL);
//            int p = semctl(lockparent,0,GETVAL);
//            printf("lockchild semaphore value %d\n" , c);fflush(stdout);
//            printf("lockparent semaphore value %d\n" , p);fflush(stdout);
            printf("            parent\n");fflush(stdout);
            semop(lockchild,&signal_op, 1);
        }
    }
    semctl(lockparent, 0, IPC_RMID);
    semctl(lockchild, 0, IPC_RMID);

}
