#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int ret;

    if ((pid == fork()) < 0)
    {
        printf("Fork error~");
        exit(1);
    }
    
    if (pid == 0)
    {
        printf("CHild waiting for any signal pid = %d",getpid());
        raise(SIGSTOP);
        exit(0);
    }
    else
    {
        if (waitpid(pid, NULL, WNOHANG) == 0)
        {
            if ((ret = kill(pid, SIGKILL) == 0))
            {
                printf("kill child \n");
            }
        }
        waitpid(pid, NULL, 0);
        exit(0);        
    }
}
/*
kill() 发送信号给进程或进程组
reise()  允许进程向自身发送信号。
 */