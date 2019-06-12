// exit() _exit() 区别在于 exit() 在终止当前进程前要检查改进程打开过哪些文件，
// 把文件缓存区的文件写回文件。 即有清理I/O缓冲操作
#include <stdio.h>
#include <stdlib.h>

int testExit();
int test_exit();

int main()
{
    testExit();
    test_exit();
}

testExit()
{
    printf("Using exit... \n");
    printf("This is the content in buffer");
    exit(0);
}

test_exit()
{
    printf("Using _exit... \n");
    printf("This is the content in buffer");
    _exit(0);
}