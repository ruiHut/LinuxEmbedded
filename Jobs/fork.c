// Fock（） 函数返回值，其中父进程返回子进程的 PID ，而子进程返回 0
// 注意线程与进程的区别 父进程结束 子进程变成孤儿进程 不会立刻结束。
// 而主线程结束，其所以子线程全部结束。
int main(void)
{
    pid_t pid;

    result = fork();
    if (result == -1)
    {
        printf("Fock error\n");
    }
    else if (result == 0)
    {
        printf("This returned value is %d\n
        In child process !!\n
        PID is %d\n", result,getpid());
    }
    else // 返回值大于 0 代表父进程
    {
        printf("This returned value is %d\n
        In father process !!\n
        PID is %d\n", result,getpid());
    }

    return result;
}