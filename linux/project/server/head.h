#include <header.h>
#include "queue.h"

// 定义线程池
typedef struct pool_s{
    // 所有子线程的id
    pthread_t *threadIds;
    // 子线程的数量
    int threadNum;
    // 任务队列
    queue_t queue;
    // 锁
    pthread_mutex_t pool_lock;
    // 条件变量
    pthread_cond_t cond;
    // 退出标记位
    // 0 表示正常 1 表示退出
    int exit_flag;
}pool_t;

// 根据指定数量创建线程池
int initPool(pool_t *pool, int num);

// 定义线程的入口函数
void *threadMain(void *p);

// 初始化连接
int initTcpSocket(int *socket_fd, char *ip, char *port);

// 添加epoll监听
int epoll_addfd(int epoll_fd, int file_fd);

// 传送文件
int sendFile(int net_fd);

// 干活
int do_worker(int net_fd);
