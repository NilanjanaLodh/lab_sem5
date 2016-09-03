#include<pthread.h>
#include<stdio.h>
#include<sys/types.h>
#include<semaphore.h>
#include<unistd.h>
 
pthread_t t1,t2;
pthread_attr_t tattr;
int counter;
sem_t mutex;
 
void* runner(void *arg)
{
int i = 0;
 
printf("Thread received %i\n", *(int*)arg);
 
for(i = 0; i < 5; i++)
{
sem_wait(&mutex);
printf("Thread %i says %i\n",*((int *)arg),counter);
counter++;
sem_post(&mutex);
sleep(1);
}
return (void*)NULL;
}
 
int main()
{
int r;
int t = 1;
 
printf("hi");
r = sem_init(&mutex,0,1);
r = pthread_attr_init(&tattr);
 
r = pthread_create(&t1,&tattr,runner,(void *)&t);
 
t = 2;
 
r = pthread_create(&t2,&tattr,runner,(void *)&t);
 
printf("Threads initialised");
r = pthread_join(t1,NULL);
r = pthread_join(t2,NULL);
r = sem_destroy(&mutex);
 
return 0;
}


////////////


#include <sys/types.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <fcntl.h>
#include <limits.h>
...
key_t semkey;
int semid, pfd, fv;
struct sembuf sbuf;
char *lgn;
char filename[PATH_MAX+1];
struct stat outstat;
struct passwd *pw;
...
/* Get unique key for semaphore. */
if ((semkey = ftok("/tmp", 'a')) == (key_t) -1) {
    perror("IPC error: ftok"); exit(1);
}

/* Get semaphore ID associated with this key. */
if ((semid = semget(semkey, 0, 0)) == -1) {

    /* Semaphore does not exist - Create. */
    if ((semid = semget(semkey, 1, IPC_CREAT | IPC_EXCL | S_IRUSR |
        S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) != -1)
    {
        /* Initialize the semaphore. */
        sbuf.sem_num = 0;
        sbuf.sem_op = 2;  /* This is the number of runs
                             without queuing. */
        sbuf.sem_flg = 0;
        if (semop(semid, &sbuf, 1) == -1) {
            perror("IPC error: semop"); exit(1);
        }
    }
    else if (errno == EEXIST) {
        if ((semid = semget(semkey, 0, 0)) == -1) {
            perror("IPC error 1: semget"); exit(1);
        }
    }
    else {
        perror("IPC error 2: semget"); exit(1);
    }
}
...