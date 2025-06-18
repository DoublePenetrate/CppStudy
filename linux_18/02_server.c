#include <func.h>
#include <time.h>
typedef struct conn{
    int net_fd; // 某个客户端链接的socket对象的文件描述符
    int alive;  // 连接是否存在: 0正常连接,   非0代表连接断开
    time_t last_time;
}conn_t;
// 群聊服务端
int main() {
    char* ip = "192.168.149.128";
    char* port = "8080";
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    int reuse = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(port));
    sockaddr.sin_addr.s_addr = inet_addr(ip);
    bind(socket_fd, (struct sockaddr*)&sockaddr, sizeof(sockaddr));

    listen(socket_fd, 10);
    conn_t list[100];
    memset(list, 0, sizeof(list));
    int size = 0;

    int epoll_fd = epoll_create(1);
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = socket_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &event);
    while (1) {
        struct epoll_event array[10];
        memset(array, 0, sizeof(array));
        int epoll_num = epoll_wait(epoll_fd, array, 2, 1000);

        
        for (int i = 0; i < epoll_num; i++) {
            if (array[i].data.fd == socket_fd) {
                // 有新连接加入进来
                int net_fd = accept(socket_fd, NULL, NULL);
                // 存入数组中
                list[size].net_fd = net_fd;
                list[size].alive = 0;
                time(&list[size].last_time);
                size++;
                event.data.fd = net_fd;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, net_fd, &event);
                printf("%d 已连接\n", net_fd);
            } else {
                // 旧连接发信息
                char buf[60] = {0};
                int net_fd = array[i].data.fd;
                int ret = recv(net_fd, buf, sizeof(buf), 0);
                if (ret == 0) {
                    for (int k = 0; k < size; k++) {
                        if (list[k].alive == 0 && list[k].net_fd == net_fd) {
                            list[k].alive = 1;
                            break;
                        }
                    }
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, net_fd, NULL);
                    close(net_fd);
                    printf("%d 已断开连接\n", net_fd);
                    continue;
                }

                // 数据转发
                for (int j = 0; j < size; j++) {
                    if (list[j].alive == 0 && list[j].net_fd != net_fd) {
                        send(list[j].net_fd, buf, sizeof(buf), 0);
                    } else if(list[j].alive == 0 && list[j].net_fd == net_fd) {
                        time(&list[j].last_time);
                    }
                }
            }
        }

        for (int k = 0; k < size; k++) {
            time_t now_time;
            time(&now_time);
            if (list[k].alive == 0 && now_time - list[k].last_time >= 30) {
                event.data.fd = list[k].net_fd;
                epoll_ctl(epoll_fd, EPOLL_CTL_DEL, list[k].net_fd, &event);
                list[k].alive = 1;
                close(list[k].net_fd);
                printf("%d 已断开连接\n", list[k].net_fd);

            }
        }
    }
    close(socket_fd);
    return 0;
}
