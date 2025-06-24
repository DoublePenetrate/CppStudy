#include <header.h>

// 定义任务队列的节点
typedef struct node_s{
    int net_fd;
    struct node_s *pNext;
}node_t;

// 定义任务队列
typedef struct queue_s{
    node_t *head;
    node_t *end;
    int size;
}queue_t;

// 入队
int enQueue(queue_t *queue, int net_fd);
//出队
int deQueue(queue_t *queue);
