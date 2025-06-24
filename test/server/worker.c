#include "head.h"

int do_worker(int net_fd) {
    // 干活了
    send(net_fd, "主人永远不要为情所困, 爱意随风起,可是你抓得住风吗?", 200, MSG_NOSIGNAL);
    return 0;
}
