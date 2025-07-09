#include "head.h"

// 初始化进程池,启动子进程,并记录子进程启动信息
int init_poll(son_t* list, int num) {
    for (int i = 0; i < num; i++) {

        //本地socket
        int local_socket[2];
        socketpair(AF_LOCAL, SOCK_STREAM, 0, local_socket);

        pid_t pid = fork();
        if (pid == 0) {
            // 子进程
            close(local_socket[0]);
            son_main(local_socket[1]);
        } else {
            // 父进程
            close(local_socket[1]);
            list[i].pid = pid;
            list[i].status = FREE;
            list[i].local_socket = local_socket[0];
        }
    }
    return 0;
}


