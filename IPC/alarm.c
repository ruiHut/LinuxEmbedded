#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int ret = alarm(5);
    pause();

    printf("I have been waken up\n")
}
/*
    alram() 为进程设置定时器，到时间后发送指定信号。
    pause() 将进程挂起，直到捕捉到信号为止。 通常用于判断信号是否到达

    此查询中 printf() 语句不会执行，因为 alram 默认返回信号为 SIGALRAM 系统动作为 “终止该进程”
 */