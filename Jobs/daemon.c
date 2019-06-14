/* 
守护进程： 后台服务进程，一种生存周期较长的进程。
    实现步骤
    1. 成为孤儿进程，即父进程退出，被 init 进程收养
        关键代码：
        pid = fork();
        if (pid > 0) exit(0);

    2. 在子进程中创建新会话
        进程组： 一个或多个进程的集合。由进程组 ID 唯一标示。
        会话期： 会话组是一个或多个进程组的集合。
        关键代码：
        setsid()
            作用： 创建一个新的会话组，并担任该组组长
            1. 让进程摆脱原会话控制
            2. 让进程摆脱原进程组控制
            3. 让进程摆脱原控制终端的控制
    
    3. 改变当前目录为根目录 (当然也可以为其他目录)
        关键代码：
        chdir("/")

    4. 重设文件权限掩码
        关键代码：
        umask(0) 作用：
                 让其子进程权限更加灵活
    5. 关闭文件描述符
        close([0, 1, 2])
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int fd;
    char *buf = "This is a Daemon \n";

    pid = fork();
    if (pid > 0)
    {
        exit(1);
    }

    setsid();

    chdir("/");

    umask(0);

    for (int i = 0; i < 3; i++)
    {
        close(i);
    }

    while (1)
    {
        if ((fd = open("/tmp/daemon.log", O_CREAT|O_WRONLY|O_APPEND, 0600)) < 0)
        {
            printf("Open file error \n");
            exit(1);
        }
        write(fd, buf, strlen(buf) + 1);
        close(fd);
        sleep(10);       
    }
    exit(0);
}