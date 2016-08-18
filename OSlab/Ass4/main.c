#include "common.c"
void print2d(int *X, int r, int c);
void input2d(int *X, int r, int c);
int running_children=0;

int main()
{
    initialize_keys();
    int shmid[6];
    int *laddr ;
    int *maddr ;
    int *naddr ;
    int *A ;
    int *B ;
    int  *C ;
    int l,m,n;

    printf("l m n : ");fflush(stdout);

    shmid[0] = shmget(key_l, sizeof(int) , def_flag );
    laddr= (int *) shmat(shmid[0] , (void*)0 , 0);
    scanf("%d", laddr);
    l= *laddr;
 //   printf("scanned l %d\n",l);

    shmid[1] = shmget(key_m, sizeof(int) , def_flag );
    maddr= (int *) shmat(shmid[1] , (void*)0 , 0);
    scanf("%d", maddr);
    m = *maddr;
 //   printf("scanned m %d\n",m);

    shmid[2] = shmget(key_n, sizeof(int) , def_flag );
    naddr= (int *) shmat(shmid[2] , (void*)0 , 0);
    scanf("%d", naddr);
    n = *naddr;
 //   printf("scanned n %d\n",n);

    shmid[3] = shmget(key_A, shm_size*sizeof(int) , def_flag );
    A= (int *) shmat(shmid[3] , (void*)0 , 0);
//  printf("alloc size %lu\n",sizeof(A));fflush(stdout);

    shmid[4] = shmget(key_B, shm_size*sizeof(int) , def_flag );
    B= (int *) shmat(shmid[4] , (void*)0 , 0);

    shmid[5] = shmget(key_C, shm_size*sizeof(int) , def_flag );
    C= (int *) shmat(shmid[5] , (int*)0 , 0);

    ///__________________________________________________
//    printf("done initializing \n");
    printf("_______A(%d x %d)_____\n",l,m);fflush(stdout);
    //A= (int *)(malloc (l*m*sizeof(int)) );
    input2d(A,l,m);
    printf("_______B(%d x %d)_____\n",m,n);fflush(stdout);
    input2d(B,m,n);

    printf("computing C= A x B in a distributed manner .. \n");fflush(stdout);
    int i,j,mychild;
    for(i=0;i<l;i++)
    {
        for(j=0;j<n;j++)
        {
            mychild = fork();

            if(mychild==0)
            {
                char istr[10] , jstr[10];
                sprintf(istr,"%d",i);
                sprintf(jstr,"%d",j);
                char* list[] = {"./compute", istr, jstr, NULL};
                execvp(list[0] , list);

                ///if the control reaches this place.. something must have gone wrong
                printf("something went wrong :( \n");fflush(stdout);
                exit(EXIT_FAILURE);
            }
            /// the child will never come to this point under any circumstance
            else
                running_children++;
        }
    }

   int x;
   while((x=waitpid(-1,0,WNOHANG))>=0) ///busy waiting
   {
       if(x>0)
           running_children -- ;
   }
   // printf("%d x \n" , x);

    if(running_children!=0)
    {
        printf("something went wrong :( \n");
    }

    /**
        waitpid() system call suspends execution of the calling process
        until a child specified by pid argument has changed state

        if pid argument = -1  : wait for any child process

        WNOHANG means return immediately if no child has exited

        waitpid(): on success, returns the process ID of the child whose state has changed; if WNOHANG was specified and one or more child(ren) specified by pid exist, but have not yet changed state, then 0 is returned.
         On error, -1 is returned.

    */
    printf("___________A___________\n");fflush(stdout);
    print2d(A,l,m);

    printf("___________B___________\n");fflush(stdout);
    print2d(B,m,n);

    printf("_______C = A x B________\n");fflush(stdout);
    print2d(C,l,n);

    shmdt(laddr);
    shmdt(maddr);
    shmdt(naddr);
    shmdt(A);
    shmdt(B);
    shmdt(C);

    for(i=0;i<6;i++)
    {
        shmctl(shmid[i], IPC_RMID, NULL);
    }
}

void print2d(int *X, int r, int c)
{
    int i,j;

    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            printf("%d ", *loc(X,r,c,i,j)); fflush(stdout);
        }
        printf("\n"); fflush(stdout);
    }
}

void input2d(int *X, int r, int c)
{
    int i,j;
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
           // printf("loc %d\n",*(X + i*c + j));fflush(stdout);
            scanf("%d",loc(X,r,c,i,j));
        }
    }
   // printf("done !\n");fflush(stdout);
}
