#include "head.h"
#include <asm-generic/socket.h>
#include <sys/socket.h>

int initTcpSocket(int *socket_fd, char *ip, char *port) {
    *socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    // 端口复用
    int reuse = 1;
    setsockopt(*socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    // 封装sockaddr结构体
    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(port));
    sockaddr.sin_addr.s_addr = inet_addr(ip);

    int ret_bind = bind(*socket_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr));
    //printf("ret_bind = %d\n", ret_bind);
    //ERROR_CHECK(ret_bind, -1, "bind");
    int ret_lis = listen(*socket_fd, 10);
    //printf("ret_listen = %d\n", ret_lis);
    return 0;
}
