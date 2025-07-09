#include "head.h"
#include <pthread.h>

// 定义线程的入口函数
void *threadMain(void *p) {
    pool_t *pool = (pool_t*)p;

    while (1) {
        // 从队列中获取net_fd
        int net_fd = 0;
        pthread_mutex_lock(&pool->pool_lock);

        while (pool->queue.size <= 0 && pool->exit_flag == 0) {
            // 当没有要求退出的信号,队列中没有任务时陷入等待
            pthread_cond_wait(&pool->cond, &pool->pool_lock);
        }
        // 走到这里时,说明任务队列中已经有任务或者有退出信号
        if (pool->exit_flag != 0) {
            // 要退出了
            printf("退出\n");
            pthread_mutex_unlock(&pool->pool_lock);
            pthread_exit(NULL);
        }
        // 说明队列中, 有新的客户端的net_fd
        net_fd = pool->queue.head->net_fd;
        //printf("net_fd = %d\n", net_fd);
        deQueue(&pool->queue);
        pthread_mutex_unlock(&pool->pool_lock);

        // sendFile(net_fd);
        do_worker(net_fd);
        close(net_fd);
    }

    return NULL;
}



