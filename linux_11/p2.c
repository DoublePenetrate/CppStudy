#include <func.h>
#define MAXLINE 1024

int main(int argc, char* argv[]) {
    int fd1 = open("pipe1", O_WRONLY);
    if (fd1 == -1) {
        error(1, errno, "open pipe1 failed");
    }
    
    int fd2 = open("pipe2", O_RDONLY);
    if (fd2 == -1) {
        error(1, errno, "open pipe2 failed");
    }
    printf("Established!\n");
    // 点对点聊天
    fd_set mainfds; // 放置感兴趣的文件描述符
    FD_ZERO(&mainfds);
    FD_SET(STDIN_FILENO, &mainfds);
    int maxfds = STDIN_FILENO;
    FD_SET(fd2, &mainfds);
    if (fd2 > STDIN_FILENO) {
        maxfds = fd2;
    }
    char rcvline[MAXLINE];
    char sndline[MAXLINE];

    for (;;) {
        fd_set readfds = mainfds; // 结构体的赋值
        int nready = select(maxfds + 1, &readfds, NULL, NULL, NULL); // timeout为NULL 一直阻塞
        switch(nready) {
        case -1: error(1, errno, "select");
        case 0: printf("TIMEOUT\n");
                break;
        default:
                // 有I/O事件就绪,轮询
                if (FD_ISSET(STDIN_FILENO, &readfds)) {
                    // stdin就绪
                    fgets(sndline, MAXLINE, stdin);
                    write(fd1, sndline, strlen(sndline) + 1);
                }

                if (FD_ISSET(fd2, &readfds)) {
                    // 管道就绪
                    read(fd2, rcvline, MAXLINE);
                    printf("From p1: %s", rcvline);
                }
                break;
        }
    }
    return 0;
}

