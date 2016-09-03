#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>

#define true 1
#define false 0

#define KEY1 (1494)
#define KEY2 (1625)

union semun
{
    int val;
    struct semid_ds *buf;
    ushort * array;
};

struct sembuf wait_op = {0, -1 , 0};
struct sembuf signal_op = {0 , 1 , 0};

