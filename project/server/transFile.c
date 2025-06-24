#include "head.h"
#include <sys/sendfile.h>

typedef struct train_s {
    int len;
    char buf[10000];
}train_t;


int sendFile(int net_fd) {
    char *file_name = "file.txt";
    // 需要O_RDWR,避免mmap权限不足
    int file_fd = open(file_name, O_RDWR);
    train_t train;
    bzero(&train, 0);

    // 获取文件信息
    struct stat stat_file;
    fstat(file_fd, &stat_file);
    
    // 发送文件长度
    send(net_fd, &stat_file.st_size, sizeof(off_t), MSG_NOSIGNAL);

    // 发送文件长度和名字
    train.len = strlen(file_name);
    memcpy(train.buf, file_name, train.len);
    send(net_fd, &train, sizeof(int) + train.len, 0); 

    sendfile(net_fd, file_fd, NULL, stat_file.st_size);
    printf("over\n");
    return 0;
}
