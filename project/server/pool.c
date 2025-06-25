#include "head.h"
#include <pthread.h>

// 根据线程数量创建线程池
int initPool(pool_t *pool, int num) {
    // 为线程id开辟空间
    pool->threadIds = (pthread_t *)calloc(num, sizeof(pthread_t));
    // 创建子线程
    for (int i = 0; i < num; i++) {
        pthread_create(&pool->threadIds[i], NULL, threadMain, pool);
    }
    // 记录子线程数量
    pool->threadNum = num;
    // 初始化任务队列
    bzero(&pool->queue, sizeof(pool->queue));
    // 初始化锁
    pthread_mutex_init(&pool->pool_lock, NULL);
    // 初始化条件变量
    pthread_cond_init(&pool->cond, NULL);
    // 初始化退出标记位
    pool->exit_flag = 0;
    return 0;
}
