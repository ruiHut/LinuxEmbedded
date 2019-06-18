/*
一个进程处于僵尸状态时虽然绝大部分数据结构（堆，栈。。） 都被回收了
但仍有以下问题
    1. 当程序处于并发状态时，该部分剩余资源仍然客观
    2. linux 提供的 PID 有限为 short 类型
    3. linux 内核对整个系统中的进程数做了最大限制

如何避免僵尸进程
     只需要父进程及时 ‘收尸’
        1. wait(), waitpid() 不仅可以获取子进程信息，还可以回收子进程资源。
            问题 wait（）为阻塞，子进程终止为随机 waitpit 不得已用轮询。
        2. 异步处理 SIGCHLD 信号机制
            调用 signal() 设置信号处理函数
        3. 忽视子进程状态， 不会产生僵尸进程
            signal(SIGCHLD, SIG_IGN);
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

// 信号处理函数，每次收到信号时触发
void sigchild_handler(int signo)
{
    wait(NULL);
    puts("SIGCHLD received!");
}

int main()
{
    pid_t pid;

    if (SIG_ERR == siganl(SIGCHLD, sigchild_handler)) {
        perror("signal");
        return -1;
    }
    
    if (-1 ==(pid = fork()))
    {
        printf("fork error\n");
        return -1;
    }
    
    if (pid == 0)
    {
        sleep(3);
        exit(EXIT_SUCCESS);
    } else
    {
        while (1)
        {
            puts("I am father! ");
            sleep(1);
        }
    }
    return 0;            
}