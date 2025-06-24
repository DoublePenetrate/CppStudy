#include "head.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>

int initPool(pool_t *pool, int num) {
    // 开辟线程池中ids空间
    pool->pthreadIds = (pthread_t *)calloc(num, sizeof(pthread_t));
    // 记录线程池中线程数量
    pool->pthread_num = num;
    // 启动子线程
    for (int i = 0; i < num; i++) {
        pthread_create(&pool->pthreadIds[i], NULL, threadMain, pool);
    }
    // 初始化任务队列
    bzero(&pool->queue, sizeof(pool->queue));

    // 初始化锁
    pthread_mutex_init(&pool->pool_lock, NULL);
    // 初始化条件变量
    pthread_cond_init(&pool->cond, NULL);
    return 0;
}
