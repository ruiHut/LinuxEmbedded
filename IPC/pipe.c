#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_DATA_LEN 256
#define DELAY_TIME   1

int main()
{
    pid_t pid;
    int pipe_fd[2];
    char buf[MAX_DATA_LEN];
    const char data[] = "pipe test program";
    int real_read, real_write;

    memset((void*)buf, 0, sizeof(buf));
    if (pipe(pipe_fd) < 0)          // 创建管道
    {
        printf("pipe crate error\n");
        exit(1);
    }
    if ((pid = fork()) == 0 )
    {
        close(pipe_fd[1]);
        sleep(DELAY_TIME * 3);

        if ((real_read = read(pipe_fd[0], buf, MAX_DATA_LEN)) > 0)
        {
            printf("%d bytes read from the pipe is '%s'\n", real_read, buf);
        }
        close(pipe_fd[0]);
        exit(0);
    }
    else if (pid > 0)
    {
        close(pipe_fd[0]);
        sleep(DELAY_TIME);
        if ((real_write = write(pipe_fd[1], data, strlen(data))) != -1)
        {
            printf("Parent wrote %d bytes : %s \n", real_read, data);
        }
        close(pipe_fd[1]);
        waitpid(pid, NULL, 0);
        exit(0);
    }
}

/*
     管道读写需要注意的几个点：
        1. 只有在管道的读端存在时，向管道写数据才有意义。否则，向管道写入数据会收到信号
        2. 向管道写入数据时， linux 不保证原子性。
        3. 父子进程在运行时，他们的先后次序不能被保证。因此，为了保证父进程已经关闭对应文件描述符。可以使用进程同步机制。
*/