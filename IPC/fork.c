#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define DELAY_TIME  3

int main(void)
{
    pid_t result;
    int sem_id;

    sem_id = semget(ftok(".". 'a'), 1, 0666|IPC_CREAT);
    init_sem(sem_id, 0);
    result = fork();
    if (result == -1)
    {
        printf("Fork error\n");
        exit(1);
    }
    else if (result == 0)
    {
        printf("child process will wait for some seconds... \n");
        sleep(DELAY_TIME);
        printf("DELAY END PID = %d", getpid());
        sem_v(sem_id);
    }
    else
    {
        sem_p(sem_id);
        printf("THE return value is %d in the father process PID = %d", getpid);
        sem_v(sem_id);
    }
    del_sem(sem_id);
    exit(0);
}