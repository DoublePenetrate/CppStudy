#include "head.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <sys/epoll.h>
#include <sys/socket.h>

int main() {
    // 初始化线程池 并启动子线程
    pool_t pool;
    initPool(&pool, 10);
    // 初始化TCP SOCKET连接
    int socket_fd;
    initTcpSocket(&socket_fd, "8080", "10.0.4.15");
    //初始化epoll并添加epoll监听
    int epoll_fd = epoll_create(1);
    epollAdd(epoll_fd, socket_fd);

    while (1) {
        struct epoll_event list[10];
        int epoll_num = epoll_wait(epoll_fd, list, 10, -1);

        for (int i = 0; i < epoll_num; i++) {
            if (list[i].data.fd == socket_fd) {
                // 说明有新连接进来
                int net_fd = accept(socket_fd, NULL, NULL);
                pthread_mutex_lock(&pool.pool_lock);
                enQueue(&pool.queue, net_fd);
                pthread_cond_signal(&pool.cond);
                pthread_mutex_unlock(&pool.pool_lock);

            }
        }
    }
    return 0;
}
