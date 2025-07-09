#include <func.h>

// 客户端代码
int main() {
    char* port = "8080";
    char* ip = "192.168.149.128";
    // 1.建立socket通信端点对象
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    // 2.封装sockaddr结构体
    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(port));
    sockaddr.sin_addr.s_addr = inet_addr(ip);
    // 3.客户端connect连接服务端
    connect(socket_fd, (struct sockaddr*)&sockaddr, sizeof(sockaddr));
    // 4.使用send和recv进行通信
    // 使用select进行同步
    fd_set set;
    while (1) {
        FD_ZERO(&set);
        FD_SET(STDIN_FILENO, &set);
        FD_SET(socket_fd, &set);
        select(socket_fd + 1, &set, NULL, NULL, NULL);

        if (FD_ISSET(STDIN_FILENO, &set)) {
            // 发送信息
            char buf[60] = {0};
            read(STDIN_FILENO, buf, sizeof(buf));
            send(socket_fd, buf, sizeof(buf), 0);
        }

        if (FD_ISSET(socket_fd, &set)) {
            // 接收信息
            char buf[60] = {0};
            int ret = recv(socket_fd, buf, sizeof(buf), 0);
            if (ret == 0) {
                printf("对方已断开连接\n");
                break;
            }
            printf("%s", buf);
        }
    }
    close(socket_fd);
    return 0;
}
