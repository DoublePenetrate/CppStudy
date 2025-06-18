#include "head.h"

// 选取空闲子进程,发送net_fd
int to_son(son_t* list, int num, int net_fd) {
    for (int i = 0; i < num; i++) {
        if (list[i].status == FREE) {
            // 把新获得的socket对象,交给这个子进程
            local_send(list[i].local_socket, net_fd);

            list[i].status = BUSY;
            break;
        }
    }

    return 0;
} 

// 子进程的逻辑

int son_main(int local_socket) {
    while (1) {
        // 1.读取本地socket -> 等待父进程发任务
        int net_fd;
        local_recv(local_socket, &net_fd);

        // 2.和客户端进行交互
        do_worker(net_fd);

        // 3.通知父进程,客户端服务完毕
        close(net_fd);
        send(local_socket, "服务完毕", 4, 0);
    }
    return 0;
}
