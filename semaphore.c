//First short method
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>

void *thread_function(void *arg);
sem_t bin_sem;
#define WORK_SIZE 1024
char WORK_AREA[WORK_SIZE];

int main() {
	int res;
	pthread_t a_thread;
	void *thread_result;
	res = sem_init(&bin_sem, 0, 0);
	if(res != 0) {
		perror("Semaphore initiation failed.");
		exit(EXIT_FAILURE);
	}
	printf("Input some text. Enter 'end' to finish.\n");
	while(strncmp("end", WORK_AREA, 3) != 0) {
		fgets(WORK_AREA, WORK_SIZE, stdin);
		sem_post(&bin_sem);
	}

	printf("\n Waiting for thread to finish...\n");
	res = pthread_join(a_thread, &thread_result);
	if(res != 0) {
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}
	printf("Thread joined\n");
	sem_destroy(&bin_sem);
	exit(EXIT_SUCCESS);
}

void *thread_function(void *arg) {
	sem_wait(&bin_sem);
	while(strncmp("end", WORK_AREA, 3) != 0) {
		printf("You input %ld characters \n", strlen(WORK_AREA) - 1);
		sem_wait(&bin_sem);
	}
	pthread_exit(NULL);
}

//Another method using SemInit.c, SemDemo.c, SemRemove.c

//SemInit.c
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/sem.h>
//int semget(key_t key, int nsems, int semflg);
union semun {
    int val;               /* used for SETVAL only */
    struct semid_ds *buf;  /* used for IPC_STAT and IPC_SET */
    ushort *array;         /* used for GETALL and SETALL */
};
int main(void) {
    key_t key;
    int semid;
    union semun arg;
    if ((key = ftok("SemDemo.c", 'J')) == -1) {   
        perror("ftok");
        exit(1); 
    }
/* create a semaphore set with 1 semaphore: */
    if ((semid = semget(key, 1, 0666 | IPC_CREAT)) == -1) {
     	perror("semget");
        exit(1); 
    }
/* initialize semaphore #0 to 1: */ arg.val = 1;
    if (semctl(semid, 0, SETVAL, arg) == -1) {
     	perror("semctl");
        exit(1); 
    }
return 0; 
}

//SemDemo.c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
int main(void) {
    key_t key;
    int semid;
    struct sembuf sb = {0, -1, 0}; /* set to allocate resource */
    if ((key = ftok("SemDemo.c", 'J')) == -1) {
        perror("ftok");
        exit(1);
    }
/* grab the semaphore set created by seminit.c: */
    if ((semid = semget(key, 1, 0)) == -1) {
        perror("semget");
        exit(1);
    }
    printf("Press return to lock: ");
        getchar();
    printf("Trying to lock...\n");
    if (semop(semid, &sb, 1) == -1) {
        perror("semop");
        exit(1);
    }
    printf("Locked.\n");
    printf("Press return to unlock: ");
    getchar();
    sb.sem_op = 1; /* free resource */
    if (semop(semid, &sb, 1) == -1) {
        perror("semop");
        exit(1);
    }
 printf("\nUnlocked\n");
    return 0;
}

//SemRemove.c
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/sem.h>
union semun {
    int val;               /* used for SETVAL only */
    struct semid_ds *buf;  /* used for IPC_STAT and IPC_SET */
    ushort *array;         /* used for GETALL and SETALL */
};
int main(void) {
    key_t key;
    int semid;
    union semun arg;
    if ((key = ftok("SemDemo.c", 'J')) == -1)  { 
      	perror("ftok");
        exit(1); 
    }
/* grab the semaphore set created by seminit.c: */ 
    if ((semid = semget(key, 1, 0)) == -1) 
    {
     	perror("semget");
        exit(1); 
    }
/* remove it: */
    if (semctl(semid, 0, IPC_RMID, arg) == -1)  {
     	perror("semctl");
        exit(1); 
    }
return 0; 
}
