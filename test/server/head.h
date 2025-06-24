#include <header.h>
#include <pthread.h>
#include <sys/socket.h>
#include "queue.h"

typedef struct pool_s{
    // 线程池的ids
    pthread_t *pthreadIds;
    // 线程池中的线程数量
    int pthread_num;
    // 任务队列
    queue_t queue;
    // 线程池的锁
    pthread_mutex_t pool_lock;
    // 线程池的条件变量
    pthread_cond_t cond;
} pool_t;

// 初始化线程池, 并启动线程
int initPool(pool_t *pool, int num);

// 初始化TCP SCOKET
int initTcpSocket(int *socket_fd, char *port, char *ip);

// 添加epoll监听
int epollAdd(int epoll_fd, int file_fd);

// 线程的入口函数
void *threadMain(void *p);

// 干活函数
int do_worker(int net_fd);
