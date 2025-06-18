#include "head.h"

int main() {
    // 启动池中进程:创建子进程(父进程创建子进程时,需要同时
    // 记录子进程的忙闲状态, 和与子进程单独通信的本地socket)
    son_t list[4];
    memset(list, 0, sizeof(list));
    init_poll(list, 4);

    // 监听端口
    int socket_fd;
    init_socket(&socket_fd, "8080", "192.168.149.128");

    // I/O多路复用
    // 创建epoll对象
    int epoll_fd = epoll_create(1);
    add_epoll(epoll_fd, socket_fd);
    for (int i = 0; i < 4; i++) {
        add_epoll(epoll_fd, list[i].local_socket);
    }

    while (1) {
        // 创建epoll就绪队列
        struct epoll_event events[4];
        memset(events, 0, sizeof(events));
        
        int epoll_num = epoll_wait(epoll_fd, events, 4, -1);
        for (int i = 0; i < epoll_num; i++) {
            int fd = events[i].data.fd;
            if (fd == socket_fd) {
                // 有新的连接进来,accept接受连接->交给空闲子进程
                int net_fd = accept(socket_fd, NULL, NULL);
                //printf("%d\n", net_fd);
                // 选取一个处于空闲状态的子进程, 把新的socket对象交给这个子进程
                to_son(list, 4, net_fd);
                close(net_fd);
            } else {
                // 子进程发来信息了,说明活干完了,修改这个子进程的忙闲状态
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
