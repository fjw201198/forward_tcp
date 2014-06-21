#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

int main() {
    int fd, fd2, fd3, rlen;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in laddr, raddr;
    bzero(&laddr, sizeof(struct sockaddr_in));  // 配置本地服务器地址
    bzero(&raddr, sizeof(struct sockaddr_in));  // 接收远程请求的地址
    laddr.sin_family = AF_INET;    
    laddr.sin_port = htons(65500);      // 本地服务器端口
    laddr.sin_addr.s_addr = htonl(INADDR_ANY);  // 接收连接的IP，此处为任意
    bind(fd, (struct sockaddr*)&laddr, sizeof(struct sockaddr_in)); //绑定
    listen(fd, 5);      // 监听
    char msg[] = "hello client, welcome to my server"; 
    char buf[128];          // 接收/发送缓冲区
    fd2 = accept(fd, (struct sockaddr*)&raddr, &rlen); // 接受一个连接请求
    printf("the client %s connect\n", inet_ntoa(raddr.sin_addr));
    write(fd2, msg, strlen(msg));
    struct sockaddr_in faddr;       // 转发服务器地址信息
    bzero(&faddr, sizeof(struct sockaddr_in));
    faddr.sin_family = AF_INET;
    faddr.sin_port = htons(65505);  // 转发服务器端口
    faddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //转发服务器地址
    fd3 = socket(AF_INET, SOCK_STREAM, 0); // 转发服务器套接字
    // 连接转发
    connect(fd3, (struct sockaddr*)&faddr, sizeof(struct sockaddr));
    while (1) {
        rlen = read(fd2, buf, sizeof(buf));
        write(1, buf, rlen); // 输出收到的信息
        write(fd3, buf, rlen);  // 转发
    }
    return 0;
}
