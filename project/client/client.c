#include <header.h>

int main() {
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    //printf("socket_fd = %d\n", socket_fd);
    char *ip = "10.0.4.15";
    char *port = "8080";
    
    struct sockaddr_in sockaddr;
    sockaddr.sin_addr.s_addr = inet_addr(ip);
    sockaddr.sin_port = htons(atoi(port));
    sockaddr.sin_family = AF_INET;

    int ret_conn = connect(socket_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr));
    //printf("ret_conn = %d\n", ret_conn);
    char buf[200] = {0};
    recv(socket_fd, buf, sizeof(buf), 0);
    printf("%s", buf);
    
    close(socket_fd);
    return 0;
}
