#include <func.h>

int main() {
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    int reuse = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    char* port = "8080";
    char* ip = "192.168.149.128";
    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(port));
    sockaddr.sin_addr.s_addr = inet_addr(ip);

    connect(socket_fd, (struct sockaddr*)&sockaddr, sizeof(sockaddr));
    
    int epoll_fd = epoll_create(1);
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = socket_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &event);
    event.data.fd = STDIN_FILENO;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &event);

    while (1) {
        struct epoll_event events[10];
        int num = epoll_wait(epoll_fd, events, 10, -1);
        int flag = 1;
        for (int i = 0; i < num; i++) {
            int cfd = events[i].data.fd;
            if (cfd == STDIN_FILENO) {
                char buf[60] = {0};
                read(STDIN_FILENO, buf, sizeof(buf));
                send(socket_fd, buf, sizeof(buf), 0);
            } else {
                char buf[60] = {0};
                int ret = recv(socket_fd, buf, sizeof(buf), 0);
                if (ret == 0) {
                    printf("服务器已断开连接\n");
                    close(socket_fd);
                    flag = 0;
                    break;
                }
                printf("%s", buf);
            }
        }
        if (flag == 0) {
            break;
        }
    }
    close(socket_fd);
    return 0;
    
}
