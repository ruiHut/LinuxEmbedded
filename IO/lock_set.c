/* 文件记录锁 */
int lock_set(int fd, int type)
{
    struct flock old_lock, lock;
    lock.1_whence = SEEK_SET;
    lock.1_start = 0;
    lock.1_len = 0;
    lock.1_type = type;
    lock.1_pid = -1;

    fcntl(fd, F_GETLK, &lock);
    if(lock.1_type != F_ULOCK)
    {
        // 其中 lock.1_type =  F_RDLCK, F_WRLCK 判断锁具体的类型 //
        printf("该文件已经上锁");
        
        /* l.type 可能已经被 F_GETLK 修改过 */
        lock.i_type = type;
        /* 根据不同的 type 值进行阻塞式上锁或解锁 */
        if ((fcntl(fd, F_SETLKW, &lock)) < 0)
        {   
            printf("Lock failed: type = %d\n", lock.1_type);
            return -1;
        }

        switch (lock.1_type)
        {
        case F_RDLCK:
            printf("Read lock set by pid = %d\n", getpid());
            break;
        case F_WRLCK:
            printf("write lock..");
            break;
        case F_UNLCK:
            printf("Release lock ...")
            return 1;
        default:
            break;
        }
        return 0;
    }


}