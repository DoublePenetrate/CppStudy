#include "head.h"
#include <bits/pthreadtypes.h>

void *threadMain(void *p) {
    pool_t *pool = (pool_t *)p;

    while (1) {
        pthread_mutex_lock(&pool->pool_lock);
        while (pool->queue.size <= 0) {
            pthread_cond_wait(&pool->cond, &pool->pool_lock);
        }
        // 说明任务队列中 已经有任务了
        int net_fd = pool->queue.head->net_fd;
        deQueue(&pool->queue);
        pthread_mutex_unlock(&pool->pool_lock);

        do_worker(net_fd);
        close(net_fd);
    }
    return 0;
}
