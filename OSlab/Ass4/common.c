#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

const char* path = "/home/hermoi-nil/Desktop/code/lab_sem5/OSlab/Ass4/common.c";

int key_l,key_m,key_n,key_A,key_B,key_C ;

#define def_flag ( 0666 | IPC_CREAT )
#define shm_size 2048
void initialize_keys()
{
     key_l = ftok(path,'l');
     key_m = ftok(path,'m');
     key_n = ftok(path,'n');
     key_A = ftok(path,'A');
     key_B = ftok(path,'B');
     key_C = ftok(path,'C');
}
inline int* loc(int* X , int r, int c, int i, int j)
{
    return (X + c*i + j) ;
}
