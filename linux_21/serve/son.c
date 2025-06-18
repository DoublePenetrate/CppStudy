#include "head.h"

int son_main(int local_socket) {
    // 子进程的主要逻辑
    while (1) {
        // 1.读取本地socket,等待父进程发任务过来
        int net_fd;
        local_recv(local_socket, &net_fd);
        // 2.完成与客户端的交互
        do_worker(net_fd);
        close(net_fd);
        // 3.通知父进程,客户端服务完毕
        send(local_socket, "123", 3, 0);
    }
}

// 从线程池中选取一个处于空闲状态的子进程, 把新的socket对象交给这个子进程
int to_son(son_t* list, int num, int net_fd) {
    for (int i = 0; i < num; i++) {
        if (list[i].status == FREE) {
            local_send(list[i].local_socket, net_fd);
            list[i].status = BUSY;
            break;
        }
    }
    return 0;
}
