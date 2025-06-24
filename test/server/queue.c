#include "queue.h"

int enQueue(queue_t *queue, int net_fd) {
    node_t *pNew = (node_t *)calloc(1, sizeof(node_t));
    pNew->net_fd = net_fd;
    if (queue->size == 0) {
        // 当队列为空时
        queue->head = pNew;
        queue->end = pNew;
        queue->size++;
        return 0;
    } 
    // 当队列不为空时
    queue->end->pNext = pNew;
    queue->end = pNew;
    queue->size++;
    return 0;
}

int deQueue(queue_t *queue) {
    // 首先判断队列是否为空
    if (queue->size == 0) {
        return -1;
    }

    // 到这 说明队列不为空
    node_t *temp = queue->head;
    queue->head = temp->pNext;
    if (queue->size == 1) {
        // 当队列中只有一个节点时
        queue->end = NULL;
    }
    queue->size--;
    free(temp);
    return 0;
}
