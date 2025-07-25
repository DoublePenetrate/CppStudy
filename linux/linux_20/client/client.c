#include <func.h>

int main() {
    char* port = "8080";
    char* ip = "192.168.149.128";

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    int reuse = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(port));
    sockaddr.sin_addr.s_addr = inet_addr(ip);
    connect(socket_fd, (struct sockaddr*)&sockaddr, sizeof(sockaddr));
    char buf[60] = {0};
    int res = recv(socket_fd, buf, sizeof(buf), 0);
    printf("%s \n", buf);
    close(socket_fd);
    return 0;

}
