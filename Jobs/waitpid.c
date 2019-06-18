#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t pc, pr;

    pc = fork();
    if (pc < 0)
    {
        printf("Fork error!\n");
    }
    else if (pc == 0) // 子进程
    {
        // 暂停五秒 正常退出。
        sleep(5);
        exit(0);
    }
    else
    {
        do
        {   
            // wati() 用于父进程阻塞，直到一个子进程结束或者该进程收到一个指定的信号为止。
            // 如果该父进程没有子进程或者子进程结束，则 wait（）立即返回
            //  waitpit（） 作用和 wait（）一样，但是可以提供一个非阻塞 wait（）功能。
            // liunx 内部实现 wait（） 实际上是调用 waitpid（）
            pr = waitpid(pc, NULL, WNOHANG);

            if (pr == 0)
            {
                printf("The child process has not exited\n");
                sleep(1);
            }
        } while (pr == 0);

        if (pr == pc)
        {
            printf("Get child exit code: %d\n", pr);
        }
        else
        {
            printf("Some error occured \n");
        }
    }
}