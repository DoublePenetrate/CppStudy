#include <func.h>

int main(int argc, char* argv[]) {
    // ./t_kill pid signo
    if (argc != 3) {
        error(1, errno, "Usage: %s pid signo", argv[0]);
    }
    pid_t pid;
    int signo;
    sscanf(argv[1], "%d", &pid);
    sscanf(argv[2], "%d", &signo);
    if (kill(pid, signo) == -1) {
        error(1, errno, "KILL");
    }
    return 0;
}
