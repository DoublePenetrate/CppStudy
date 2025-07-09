#include <func.h>

void print_ids(const char* prefix) {
    printf("%s: pid = %d, ppid = %d, tid = %lx\n",
           prefix,
           getpid(),
           getppid(),
           pthread_self());
}

int main() {
    print_ids("main thread");
    return 0;
}
