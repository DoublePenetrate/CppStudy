#include "head.h"

int init_pool(son_t* list, int num) {
    for (int i = 0; i < num; i++) {
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
