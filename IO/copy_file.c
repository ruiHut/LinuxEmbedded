#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 1024
#define SRC_FILE_NAME "src_file"
#define DSET_FILE_NAME "dest_file"
#define OFFSET  10240

/* 从一个文件中读取最后 10KB 数据并复制到另一个文件 */
int main()
{
    int src_file, dest_file;
    unsigned char buff[BUFFER_SIZE];
    int real_read_len;

    src_file = open(SRC_FILE_NAME, O_RDONLY);

    dest_file = open(DSET_FILE_NAME, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR
    |S_IRGRP|S_IROTH);
    if (src_file < 0 || dest_file < 0)
    {
        printf("Open file error\n");
        exit(0);
    }
    
    /* 将源文件的读/写指针移到最后 10KB 的起始位置 */
    lseek(src_file, -OFFSET, SEEK_END);

    while ((real_read_len = read(src_file, buff, sizeof(buff))) > 0)
    {
        write(dest_file, buff, real_read_len);
    }
    
    close(dest_file);
    close(src_file);
    return 0;
}