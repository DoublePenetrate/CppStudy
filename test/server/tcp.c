#include "head.h"
#include <asm-generic/socket.h>
#include <netinet/in.h>
#include <sys/socket.h>

int initTcpSocket(int *socket_fd, char *port, char *ip) {
    // 创建网络通信对象端点socket
    *socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    // 复用端口ip
    int reuse = 1;
    setsockopt(*socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    // 填充sockaddr对象
    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(port));
    sockaddr.sin_addr.s_addr = inet_addr(ip);

    // 绑定sockaddr对象
    int ret_bind = bind(*socket_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr));
   // printf("ret_bind = %d\n", ret_bind);
    // 监听socket对象
    listen(*socket_fd, 10);
    
    return 0;
}
