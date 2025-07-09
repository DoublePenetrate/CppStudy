#include "queue.h"

// 入队
int enQueue(queue_t *pQueue, int net_fd) {
    node_t *pNew = (node_t*)calloc(1, sizeof(node_t));
    pNew->net_fd = net_fd;
    if (pQueue->size == 0) {
        // 队列为空
        pQueue->end = pNew;
        pQueue->head = pNew;
        pQueue->size++;
    } else {
        // 队列不为空
        pQueue->end->pNext = pNew;
        pQueue->end = pNew;
        pQueue->size++;
    }
    return 0;
}

// 出队
int deQueue(queue_t *pQueue) {
    // 当队列为空时,报错返回-1
    if (pQueue->size == 0) {
        return -1;
    }
    // 走到这,说明队列不为空
    node_t *temp = pQueue->head;
    if (pQueue->size == 1){
        // 当队列长度为1时,需要额外处理队列尾节点
        pQueue->end = NULL;
    }
    pQueue->head = pQueue->head->pNext;
    free(temp);
    pQueue->size--;
    return 0;
}
