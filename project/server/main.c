#include "head.h"
#include <pthread.h>
#include <sys/epoll.h>

int pipe_fd[2];
void func(int num) {
    write(pipe_fd[1], "1", 1);
    return;
}

int main() {
    pipe(pipe_fd);

    if (fork() != 0) {
        // 父进程
        signal(2, func);
        wait(NULL);
        exit(0);
    }

    // 子进程
    setpgid(0, 0);
    close(pipe_fd[1]);
    // 初始化线程池并启动线程
    pool_t pool;
    initPool(&pool, 5);
    // 创建TCP SOCKET
    int socket_fd;
    initTcpSocket(&socket_fd, "10.0.4.15", "8080");
    //printf("socket_fd = %d\n", socket_fd); 
    // 创建epoll对象并添加epoll监听  
    int epoll_fd = epoll_create(1);
    //printf("epoll_fd = %d\n", epoll_fd);
    epoll_addfd(epoll_fd, socket_fd);
    epoll_addfd(epoll_fd, pipe_fd[0]);
    while (1) {

        struct epoll_event list[5];
        memset(list, 0, sizeof(list));
        
        int epoll_num = epoll_wait(epoll_fd, list, 5, -1);
        //printf("epoll_num = %d\n", epoll_num);
        // 遍历就绪集合
        for (int i = 0; i < epoll_num; i++) {
            int fd = list[i].data.fd;
            if (fd == socket_fd) {
                // 说明有新连接进来了
                int net_fd = accept(socket_fd, NULL, NULL);
                //printf("net_fd = %d\n", net_fd);            
                pthread_mutex_lock(&pool.pool_lock);
                enQueue(&pool.queue, net_fd);
                
                pthread_cond_signal(&pool.cond);
                pthread_mutex_unlock(&pool.pool_lock);
                
              } else if (fd == pipe_fd[0]) {
                // 说明有信号过来
                // 通知子线程退出
                pthread_mutex_lock(&pool.pool_lock);
                pool.exit_flag = 1;
                pthread_cond_broadcast(&pool.cond);
                pthread_mutex_unlock(&pool.pool_lock);

                // 等待子线程退出
                for (int j = 0; j < pool.threadNum; j++) {
                    pthread_join(pool.threadIds[j], NULL);
                }
                // 主线程退出
                pthread_exit(NULL);
            }        
        }
    }
    return 0;
}
