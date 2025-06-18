#include "head.h"

int main() {
    // 初始化进程池:创建子进程
    // 在父进程创建子进程的的同时,需要记录子进程
    // 的忙闲状态和与子进程通信的本地socket
    son_t list[4];
    memset(list, 0, sizeof(list));
    init_pool(list, 4);

    // 监听端口
    int socket_fd;
    init_socket(&socket_fd, "8080", "192.168.149.128");

    // I/O多路复用
    int epoll_fd = epoll_create(1);
    add_epoll(epoll_fd, socket_fd);
    for (int i = 0; i < 4; i++) {
        add_epoll(epoll_fd, list[i].local_socket);
    }

    while (1) {
        struct epoll_event events[4];
        memset(events, 0, sizeof(events));
        int epoll_num = epoll_wait(epoll_fd, events, 4, -1);
        for (int i = 0; i < epoll_num; i++) {
            int fd = events[i].data.fd;
            if (fd == socket_fd) {
                // 说明有新连接到来, accept新连接,并发送给空闲的子进程
                int net_fd = accept(fd, NULL, NULL);
                // 选取一个处于空闲状态的子进程, 把新的socket对象交给这个子进程
                to_son(list, 4, net_fd);
                close(net_fd);
            } else {
                // 说明子进程发信息过来,子进程活干完了
                // 需要修改子进程的忙闲状态
                char buf[60] = {0};
                recv(fd, buf, sizeof(buf), 0);

                for (int j = 0; j < 4; j++) {
                    if (list[j].local_socket == fd) {
                        list[j].status = FREE;
                        break;
                    }
                }
            }
        }
    }
    return 0;
}
