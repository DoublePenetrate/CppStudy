#include "head.h"
#include <sys/epoll.h>

int epollAdd(int epoll_fd, int file_fd) {
    struct epoll_event event;
    event.data.fd = file_fd;
    event.events = EPOLLIN;

    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, file_fd, &event);

    return 0;
}
