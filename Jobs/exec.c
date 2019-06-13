#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int testExeclp();
int testExecl();

int main() 
{
    testExeclp();
    testExecl();
}

testExeclp()
{
    if (fork() == 0)
    {
        int ret;
        if ((ret = execlp("ps", "ps", "-ef", NULL)) < 0)
        {
            printf("Rxeclp error \n");
        }
        
    }
}

testExecl()
{
    if (fork() == 0)
    {
        int ret;
        if ((ret = execl("/bin/ps", "ps", "-ef", NULL)) < 0)
        {
            printf("Rxeclp error \n");
        }
    }
}