#include <func.h>
#define CWDSIZE 256

int main(int argc, char* argv[]) {
    if (argc != 2) {
        error(1, 0, "Usage: %s dir", argv[0]);
    }
    pid_t pid = fork();
    char buf[CWDSIZE];
    switch(pid) {
    case -1:
        error(1, errno, "fork");
        break;
    case 0:
        // child
        getcwd(buf, CWDSIZE);
        printf("Child's cwd: %s\n", buf);

        chdir(argv[1]);
        sleep(5);
        getcwd(buf, CWDSIZE);
        printf("Child's cwd: %s\n", buf);

        _exit(0);
    default:
        getcwd(buf, CWDSIZE);
        printf("Parent's cwd: %s\n", buf);

        getcwd(buf, CWDSIZE);
        printf("Parent's cwd: %s\n", buf);
        exit(0);
    }
}
