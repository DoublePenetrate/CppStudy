#pragma once

#include <header.h>

typedef enum {
    CMD_TYPE_PWD = 1,
    CMD_TYPE_LS,
    CMD_TYPE_CD,
    CMD_TYPE_MKDIR,
    CMD_TYPE_RMDIe,
    CMD_TYPE_PUTS,
    CMD_TYPE_GETS,
    CMD_TYPE_NOTCMD //不是命令
}CmdType;

typedef struct {
    int len;        // 记录内容长度
    CmdType type;   // 消息类型
    char buf[1024]; // 记录内容本身
}train_t;

int tcpConnect(const char *ip, const char *port);

int recvn(int socket_fd, void *buf, int len);

int sendn(int socket_fd, const void *buf, int len);

int parseCommand(const char *input, int len, train_t *pt);

// 判断一个字符串是什么命令
int getCommandType(const char *str);

// 添加epoll监听
int epollAdd(const int epoll_fd, const int file_fd);
