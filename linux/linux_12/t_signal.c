#include <func.h>
#include <signal.h>

void handler(int signo) {
    switch (signo) {
    case SIGINT:
        printf("Caught SIGINT\n");
        break;
    case SIGTSTP:
        printf("Caught SIGTSTP\n");
        break;
    }
}

int main(int argc, char* argv[]) {
    sighandler_t oldhandler = signal(SIGINT, handler);
    if (oldhandler == SIG_ERR) {
        error(1, errno, "signal SIGINT");
    }

    oldhandler = signal(SIGTSTP, handler);
    if (oldhandler == SIG_ERR) {
        error(1, errno, "Caught SIGTSTP");
    }

    for(;;);
    return 0;
}
