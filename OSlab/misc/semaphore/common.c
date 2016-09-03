#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>
#define KEY (1694)

union semun
{
    int val;
    struct semid_ds *buf;
    ushort * array;
};


