#include "head.h"
#include <pthread.h>

// 定义线程的入口函数
void *threadMain(void *p) {
    pool_t *pool = (pool_t*)p;

    while (1) {
        pthread_mutex_lock(&pool->pool_lock);
        int net_fd;

        while (pool->queue.size <= 0) {
            // 当任务队列中没有任务时,陷入等待
            pthread_cond_wait(&pool->cond, &pool->pool_lock);
        }
        // 走到这里时,说明任务队列中已经有任务
        net_fd = pool->queue.head->net_fd;
        deQueue(&pool->queue);
        pthread_mutex_unlock(&pool->pool_lock);

        // sendFile(net_fd);
        do_worker(net_fd);
        close(net_fd);
    }

    return 0;
}

int do_worker(int net_fd) {
    send(net_fd, "主人永远不要为情所困,爱意随风起,可是你抓得住风吗?", 200, 0);
}
