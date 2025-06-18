#include <func.h>

int main(){

    char *ip = "192.168.149.128";
    char *port = "8080";

    int socketfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(atoi(port));

    connect(socketfd, (struct sockaddr *)&addr, sizeof(addr));
    int file_name_len=0;
    recv(socketfd, &file_name_len, sizeof(int), 0);

    char file_name[60]={0};
    recv(socketfd, file_name, file_name_len, 0);


    int buf_len=0;
    recv(socketfd, &buf_len, sizeof(int), 0);

    char buf[200]={0};
    recv(socketfd, buf, buf_len, 0);


    printf("file_name: %s \nbuf: %s \n", file_name, buf);

    int file_fd = open(file_name, O_RDWR|O_CREAT, 0600);
    write(file_fd, buf, buf_len);
    close(file_fd);

    close(socketfd);
    return 0;
}
