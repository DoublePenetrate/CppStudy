#include <func.h>

int main() {
    // 创建socket对象
    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    // 绑定端口和IP
    char* port = "8080";
    char* ip = "192.168.149.128";

    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(port));
    sockaddr.sin_addr.s_addr = inet_addr(ip);

    bind(socket_fd, (struct sockaddr*)&sockaddr, sizeof(sockaddr));

    while (1) {
        char buf[60] = {0};
        struct sockaddr_in recv_addr;
        socklen_t recvlen;
        recvfrom(socket_fd, buf, sizeof(buf), 0, (struct sockaddr*)&recv_addr, &recvlen);
        printf("from %s: %s\n", inet_ntoa(recv_addr.sin_addr), buf);
        memset(buf, 0, sizeof(buf));
        read(STDIN_FILENO, buf, sizeof(buf));
        sendto(socket_fd, buf, sizeof(buf), 0, (struct sockaddr*)&recv_addr, sizeof(recv_addr));
    }
    return 0;
}
