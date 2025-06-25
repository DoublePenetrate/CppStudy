#include "head.h"

int do_worker(int net_fd) {
    send(net_fd, "爱意随风起,风止意难平\n", 35, MSG_NOSIGNAL);
    return 0;
}
