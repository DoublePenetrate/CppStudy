#include "head.h"

int do_worker(int net_fd) {
    send(net_fd, "客官想点什么妹子为您服务呢?", 60, 0);
    return 0;
}
