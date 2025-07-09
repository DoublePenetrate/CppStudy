#include "client.h"
#include "str_utl.h"
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/epoll.h>

int tcpConnect(const char *ip, const char *port) {
    // 创建scoket对象
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("socket");
        return -1;
    }
    // 封装sockaddr对象
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(port));
    addr.sin_addr.s_addr = inet_addr(ip);
    
    // 建立TCP连接
    int ret_conn = connect(socket_fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret_conn < 0) {
        perror("connect");
        close(socket_fd);
        return -1;
    }
    return socket_fd;
}

int epollAdd(const int epoll_fd, const int file_fd) {
    // 封装epoll_event 对象
    struct epoll_event event;
    event.data.fd = file_fd;
    event.events = EPOLLIN;

    // 添加epoll监听对象
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, file_fd, &event);

    return 0;
}

// 确定接收len字节数据
int recvn(int socket_fd, void *buf, int len) {
    // left 表示还需要接收的字节数
    int left = len;
    char *pbuf = buf;
    // ret表示已经接收数据的字节数
    int ret = 0;
    while (left > 0) {
        ret = recv(socket_fd, pbuf, left, 0);
        if (ret == -1) {
            perror("recv");
            return -1;
        }
        left -= ret;
        pbuf += ret;
    }
    // 当退出循环时, left == 0
    return len - left;
}

// 确定发送len字节数据
int sendn(int socket_fd, const void *buf, int len){
    // left 表示还需要发送的字节数
    int left = len;
    const char *pbuf = buf;
    // ret返回已经传送的字节数
    int ret = 0;
    while (left > 0) {
        ret = send(socket_fd, pbuf, left, 0);
        if (ret == -1) {
            perror("send");
            return -1;
        }
        left -= ret;
        pbuf += ret;
    }
    return len - left;
}

// 解析命令
int parseCommand(const char *input, int len, train_t *pt) {
    char *pstrs[10] = {0};
    int cnt = 0;
    splitString(input, " ", pstrs, 10, &cnt);
    pt->type = getCommandType(pstrs[0]);
    // 命令的格式为:
    // 1. cmd
    // 2. cmd content
    if (cnt > 1) {
        pt->len = strlen(pstrs[1]);
        strncpy(pt->buf, pstrs[1], pt->len);
    }
    return 0;
}

// 判断一个字符串是什么命令
int getCommandType(const char *str) {
    if (!strcmp(str, "pwd"))
        return CMD_TYPE_PWD;
    else if (!strcmp(str, "ls"))
        return CMD_TYPE_LS;
    else if (!strcmp(str, "cd"))
        return CMD_TYPE_CD;
    else if (!strcmp(str, "mkdir")) 
        return CMD_TYPE_MKDIR;
    else if (!strcmp(str, "rmdir")) 
        return CMD_TYPE_RMDIR;
    else if (!strcmp(str, "puts"))
        return CMD_TYPE_PUTS;
    else if (!strcmp(str, "gets"))
        return CMD_TYPE_GETS;
    else 
        return CMD_TYPE_NOTCMD;

}
