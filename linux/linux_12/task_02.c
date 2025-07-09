#include <func.h>

int main(int argc, char* argv[]) {
    //  使用该程序给 task_01 程序发送信号
    if (argc != 3) {
        error(1, 0, "Usage: %s signo pid", argv[0]);
    }
    //  参数转化
     int signo;
     pid_t pid;
     sscanf(argv[1], "%d", &signo);
     sscanf(argv[2], "%d", &pid);

     if (kill(pid, signo) == -1) {
         error(1, errno, "kill");
     }
     return 0;
}
