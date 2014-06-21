#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

int main() {
    int fd, fd2, rlen;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in laddr, raddr;
    bzero(&laddr, sizeof(struct sockaddr_in));
    bzero(&raddr, sizeof(struct sockaddr_in));
    laddr.sin_family = AF_INET;
    laddr.sin_port = htons(65505);  // 本服务器端口
    laddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 监听连接的地址
    bind(fd, (struct sockaddr*)&laddr, sizeof(struct sockaddr_in));
    listen(fd, 5); // 监听
    char buf[128];
    fd2 = accept(fd, (struct sockaddr*)&raddr, &rlen); // 接收一个连接
    printf("the client %s connect\n", inet_ntoa(raddr.sin_addr));
    while (1) { 
        rlen = read(fd2, buf, sizeof(buf)); // 读取信息
        write(1, buf, rlen);  // 输出信息
   }
    return 0;
}
