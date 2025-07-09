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
    
    fd_set base_set;
    FD_ZERO(&base_set);
    FD_SET(socket_fd, &base_set);
    
    while (1) {
        fd_set set;
        FD_ZERO(&set);
        memcpy(&set, &base_set, sizeof(set));
        struct timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0;

        select(10, &set, NULL, NULL, &tv);
        if (FD_ISSET(socket_fd, &set)) {
            int net_fd = accept(socket_fd, NULL, NULL);
            list[size].net_fd = net_fd;
            list[size].alive = 0;
            time(&list[size].last_time);
            size++;
            FD_SET(net_fd, &base_set);
            printf("%d已连接\n", list[size - 1].net_fd);
        }

        // 判断是否有客户发信息,确认是那个客户端
        // 然后遍历所有的记录的客户端连接net_fd
        for (int i = 0; i < size; i++) {
            if (list[i].alive == 0 && FD_ISSET(list[i].net_fd, &set)) {
                char buf[60] = {0};
                int ret = recv(list[i].net_fd, buf, sizeof(buf), 0);
                if (ret == 0) {
                    printf("%d已断开连接\n", list[i].net_fd);
                    FD_CLR(list[i].net_fd, &base_set);
                    list[i].alive = 1;
                    close(list[i].net_fd);
                    continue;
                }
                for (int j = 0; j < size; j++) {
                    if (list[j].alive == 0 && list[j].net_fd != list[i].net_fd) {
                        send(list[j].net_fd, buf, sizeof(buf), 0);
                    }
                }
                time(&list[i].last_time);
            }
        }
        for (int k = 0; k < size; k++) {
            time_t now_time;
            time(&now_time);

            if (list[k].alive == 0 && now_time - list[k].last_time >= 30) {
                FD_CLR(list[k].net_fd, &base_set);
                list[k].alive = 1;
                close(list[k].net_fd);
            }
        }
    }
    close(socket_fd);
    return 0;
}
