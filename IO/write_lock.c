/* 写入锁测试用例 */

int main(void)
{
    int fd;

    fd = open("hello", O_RDWR | O_CREAT, 0644);
    if(fd < 0)
    {
        printf("Open file error\n");
        exit(1);
    }

    lock_set(fd, F_WRLCK);
    getchar();
    lock_set(fd, F_UNLCK);
    getchar();
    close(fd);
    exit(0);
}