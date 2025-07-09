#include <func.h>

enum {
    FREE,
    BUSY
};

typedef struct son_s {
    pid_t pid;
    int status;
    int local_socket;
}son_t;

int init_pool(son_t* list, int num);

int init_socket(int* socket_fd, char* port, char* ip);

int add_epoll(int epoll_fd, int fd);

int son_main(int local_socket);

int to_son(son_t* list, int num, int net_fd);

int do_worker(int net_fd);

int local_send(int local_socket, int net_fd);

int local_recv(int local_socket, int* net_fd);

