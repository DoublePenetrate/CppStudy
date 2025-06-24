#include "head.h"
#include <pthread.h>
#include <sys/epoll.h>

int main() {
    // 初始化线程池并启动线程
    pool_t pool;
    initPool(&pool, 5);
    // 创建TCP SOCKET
    int socket_fd;
    initTcpSocket(&socket_fd, "10.0.4.15", "8080");
    // 创建并添加epoll监听  
    int epoll_fd = epoll_create(1);
    epoll_addfd(epoll_fd, socket_fd);

    while (1) {

        struct epoll_event list[5];
        memset(list, 0, sizeof(list));
        
        int epoll_num = epoll_wait(epoll_fd, list, 5, -1);
        // 遍历就绪集合
        for (int i = 0; i < epoll_num; i++) {
            if (list[i].data.fd == socket_fd) {
                // 说明有新连接进来了
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
