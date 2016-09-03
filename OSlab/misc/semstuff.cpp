#include "semstuff.hpp"

key_t getSemaphoreKey(char id) {
	key_t semkey;
	
	/* Get unique key for semaphore. */
	if ((semkey = ftok("/tmp", id)) == (key_t) -1) {
	    perror("IPC error: ftok"); exit(1);
	}
	printf("semkey A: %d\n", semkey);
	return semkey;
}

int getSemaphore(key_t semkey) {
	int semid = 0;
	struct sembuf sbuf;
	
	/* Get semaphore ID associated with this key. */
	if ((semid = semget(semkey, 0, 0)) == -1) {

	    /* Semaphore does not exist - Create. */
	    if ((semid = semget(semkey, 1, IPC_CREAT | IPC_EXCL | S_IRUSR |
	        S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) != -1)
	    {
	        /* Initialize the semaphore. */
	        sbuf.sem_num = 0;
	        sbuf.sem_op = 1;  /* This is the number of runs
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
	
	printf("semid: %d\n", semid);
	
	return semid;
}