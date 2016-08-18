#include "common.c"

int main(int argc, char **argv)
{
    initialize_keys();
    //printf("argc is %d\n",argc);fflush(stdout);
    if(argc!=3)
        exit(EXIT_FAILURE);

    int i=atoi(argv[1]);
    int j=atoi(argv[2]);

   // printf("i, j in child : %d %d\n",i,j);fflush(stdout);
    int shmid;
    int *laddr , *maddr , *naddr , *A , *B , *C ;
    int l,m,n;

    shmid = shmget(key_l, sizeof(int) , def_flag );
    laddr= (int *) shmat(shmid , (void*)0 , 0);
    l= *laddr;

    shmid = shmget(key_m, sizeof(int) , def_flag );
    maddr= (int *) shmat(shmid , (void*)0 , 0);
    m = *maddr;

    shmid = shmget(key_n, sizeof(int) , def_flag );
    naddr= (int *) shmat(shmid , (void*)0 , 0);
    n = *naddr;

    shmid = shmget(key_A, shm_size*sizeof(int) , def_flag );
    A= (int *) shmat(shmid , (void*)0 , 0);

    shmid = shmget(key_B, shm_size*sizeof(int) , def_flag );
    B= (int *) shmat(shmid , (void*)0 , 0);

    shmid = shmget(key_C, shm_size*sizeof(int) , def_flag );
    C= (int *) shmat(shmid , (void*)0 , 0);

    ///__________________________________________________

    //now we are going to compute C[i, j]

    int acc=0;
    int k;
    int aval, bval;
    for(k=0;k<m;k++)
    {
        aval = (*loc(A,l,m,i,k));
        bval = (*loc(B,m,n,k,j));
       // printf("%d %d \n",aval,bval);
        acc += (aval * bval) ;
    }

 //   printf("%d , %d = %d\n",i,j,acc);fflush(stdout);
    *loc(C,l,n,i,j) = acc;
    shmdt(laddr);
    shmdt(maddr);
    shmdt(naddr);
    shmdt(A); 
    shmdt(B);
    shmdt(C);
    exit(EXIT_SUCCESS);

}
