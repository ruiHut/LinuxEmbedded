#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() 
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