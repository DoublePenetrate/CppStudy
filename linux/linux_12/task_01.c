#include <func.h>
void handler(int signo) {
    switch (signo) {
    case SIGINT: 
        printf("Caught SIGINT\n");
        break;
    case SIGQUIT:
        printf("caught SIGQUIT\n");
        break;
    case SIGTSTP:
        printf("caught SIGTSTP\n");
        break;
    default:
        printf("unknown signal\n");
        break;
    }
}

int main(int argc, char* argv[]) {
    // 1. 分别捕获 SIGINT、SIGQUIT、和 SIGSTOP
    

    sighandler_t oldhandler = signal(SIGINT, handler);
    if (oldhandler == SIG_ERR) {
        error(1, errno, "signal SIGINT");
    }
    
    oldhandler = signal(SIGQUIT, handler);
    if (oldhandler == SIG_ERR) {
       error(1, errno, "signal SIGQUIT"); 
    }

    oldhandler = signal(SIGTSTP, handler);
    if (oldhandler == SIG_ERR) {
        error(1, errno, "signal SIGTSTP");
    }
    for (;;) {
        sleep(5);
    }
    return 0;
}
