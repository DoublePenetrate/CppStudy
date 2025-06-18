#include <func.h>

int main() {
    // 创建socket对象
    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    // 封装目标ip和端口
    char* ip = "192.168.149.128";
    char* port = "8080";
    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(port));
    sockaddr.sin_addr.s_addr = inet_addr(ip);
    
    while (1) {
        char buf[60] = {0};
        read(STDIN_FILENO, buf, sizeof(buf));
        sendto(socket_fd, buf, sizeof(buf), 0, (struct sockaddr*)&sockaddr, sizeof(sockaddr));
        memset(buf, 0, sizeof(buf));
        struct sockaddr_in recv_addr;
        socklen_t addrlen;
        recvfrom(socket_fd, buf, sizeof(buf), 0, (struct sockaddr*)&recv_addr, &addrlen);
        printf("from %s: %s\n", inet_ntoa(recv_addr.sin_addr), buf);
    }
    return 0;
}
