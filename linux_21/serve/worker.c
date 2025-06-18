#include "head.h"

int do_worker(int net_fd) {
    char* file_name = "test.txt";
    int file_fd = open(file_name, O_RDONLY);
    char buf[200] = {0};
    int file_name_len = strlen(file_name);
    send(net_fd, &file_name_len, sizeof(int), 0);
    printf("server: %d\n", file_name_len);
    send(net_fd, file_name, file_name_len, 0);
    printf("server: %s\n", file_name);
    
    int ret = read(file_fd, buf, sizeof(buf));
    printf("server: %d\n", ret);
    printf("server: %s\n", buf);
    send(net_fd, &ret, sizeof(int), 0);
    send(net_fd, buf, ret, 0);
    
    //printf("hello\n");
    //send(net_fd, "hello", 5, 0);
    
    return 0;
}
