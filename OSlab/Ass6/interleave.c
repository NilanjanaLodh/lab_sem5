#include "common.c"

int main()
{
    int lockparent = semget(KEY1, 1 , 0666|IPC_CREAT);
    int lockchild  = semget(KEY2, 1 , 0666|IPC_CREAT);

    int key_x = ftok("./", 'x');
    int shmid_x= shmget(key_x,sizeof(int), 0666|IPC_CREAT);
    int *xaddr = shmat(shmid_x, NULL , 0);

    printf("> n : ");
    int n;
    scanf("%d", &n);

    int mychild= fork();

    if(mychild==0)
    {
        /**
        The child process will increment the semaphore
         But this should happen only after the parent process has finished reading the factorial
        */
        while(n--)
        {
            semop(lockchild,&wait_op, 1);
            xaddr[0]++;
           // printf("child \n");fflush(stdout);
            semop(lockparent,&signal_op, 1);

        }
    }
    else
    {
        int val;
        char valstr[100];
        int sec_child;
        while(n--)
        {
            semop(lockparent , &wait_op , 1);
          //  printf("            parent\n");fflush(stdout);
            val = xaddr[0];
            semop(lockchild,&signal_op, 1);


            sprintf(valstr,"%d",val);
            char *arglist[3]={"./factorial", valstr, NULL};
            sec_child= fork();
            if(sec_child == 0)
            {
                execvp(arglist[0], arglist);

                printf("something went wrong in the factorial method \n");fflush(stdout);
                exit(EXIT_FAILURE);
            }

        }
    }


    shmdt(xaddr);
    semctl(lockparent, 0 , IPC_RMID);
    semctl(lockchild, 0, IPC_RMID);
    shmctl(shmid_x,IPC_RMID,NULL);

}
