#include "client.h"
#include <sys/epoll.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3){
        write(STDERR_FILENO, "argc != 3\n", 10);
        exit(1);
    }
    // 建立tcp连接
    int socket_fd = tcpConnect(argv[1], argv[2]);
    // 创建epoll对象并监听
    int epoll_fd = epoll_create(1);
    epollAdd(epoll_fd, STDIN_FILENO);
    epollAdd(epoll_fd, socket_fd);
    char buf[128] = {0};
    train_t t;
    while (1) {
        struct epoll_event list[100];
        int epoll_num = epoll_wait(epoll_fd, list, 100, -1);
        for (int i = 0; i < epoll_num; i++) {
            int fd = list[i].data.fd;
            if (fd == STDIN_FILENO) {
                memset(buf, 0, sizeof(buf));
                // 读标准输入中的数据
                int ret = read(STDIN_FILENO, buf, sizeof(buf));
                if (ret == 0) {
                    printf("拜拜了您嘞\n");
                    close(socket_fd);
                    return 0;
                }
                memset(&t, 0, sizeof(t));
                // 解析命令行
                buf[strlen(buf) - 1] = '\0';
                parseCommand(buf, strlen(buf), &t);
                sendn(socket_fd, &t, 4 + 4 + t.len);
                
            } else if (fd == socket_fd) {
                // 服务器发来信息
                recv(socket_fd, buf, sizeof(buf), 0);
                printf("recv: %s\n", buf);
            }
        }

    }
    close(socket_fd);
    return 0;
}
