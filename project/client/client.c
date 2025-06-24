#include <header.h>

int main() {
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    char *ip = "10.0.4.15";
    char *port = "8080";
    
    struct sockaddr_in sockaddr;
    sockaddr.sin_addr.s_addr = inet_addr(ip);
    sockaddr.sin_port = htons(atoi(port));
    sockaddr.sin_family = AF_INET;

    connect(socket_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr));

    char buf[200] = {0};
    recv(socket_fd, buf, sizeof(buf), 0);
    printf("%s\n", buf);
    
    close(socket_fd);
    return 0;
}
