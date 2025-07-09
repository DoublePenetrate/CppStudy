#include <func.h>

// 服务端代码
int main() {
    char* port = "8080";
    char* ip = "192.168.149.128";
    // 1.建立socket通信端点对象
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    // 设置setsockopt,使socket能够重新使用处于time_wait端口
    int reuse = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    // 2.封装sockaddr结构体
    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(port));
    sockaddr.sin_addr.s_addr = inet_addr(ip);
    // 3.使用bind绑定端口和IP
    bind(socket_fd, (struct sockaddr*)&sockaddr, sizeof(sockaddr));
    // 4.使用listen进行监听
    listen(socket_fd, 10);
    // 5.使用send和recv进行通信
    // 使用select进行同步
    int connect_fd;
    fd_set set;
    FD_ZERO(&set);
    FD_SET(socket_fd, &set);
    // FD_SET(STDIN_FILENO, &set);
    while (1) {
        fd_set read_set;
        FD_ZERO(&read_set);
        memcpy(&read_set, &set, sizeof(set));
        select(10, &read_set, NULL, NULL, NULL);
        if (FD_ISSET(socket_fd, &read_set)) {
            connect_fd = accept(socket_fd, NULL, NULL);
            FD_ZERO(&set);
            FD_SET(connect_fd, &set);
            FD_SET(STDIN_FILENO, &set);
            FD_CLR(socket_fd, &set);
            printf("--对方已上线--\n");
        }
        
        if (FD_ISSET(connect_fd, &read_set)) {
            // 接收信息
            char buf[60] = {0};
            int ret = recv(connect_fd, buf, sizeof(buf), 0);
            if (ret == 0) {
                printf("---对方已断开连接---\n");
                FD_CLR(connect_fd, &read_set);
                FD_CLR(STDIN_FILENO, &read_set);
                // FD_ZERO(&set);
                FD_SET(socket_fd, &set);
                close(connect_fd);
                continue;
            }
            printf("%s", buf);
        }
        if (FD_ISSET(STDIN_FILENO, &read_set)) {
            // 发送信息
            char buf[60] = {0};
            read(STDIN_FILENO, buf, sizeof(buf));
            send(connect_fd, buf, sizeof(buf), 0);
        }

    }
    close(connect_fd);
    close(socket_fd);
    return 0;
}
