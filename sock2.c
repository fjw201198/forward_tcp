#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>

int main() {
    int fd;
    struct sockaddr_in saddr; // 服务器地址
    int rlen;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&saddr, sizeof(struct sockaddr_in));
    saddr.sin_family=AF_INET;
    saddr.sin_port = htons(65500);  // 服务器端口号
    saddr.sin_addr.s_addr = inet_addr("192.168.56.1"); // 本客户端地址
    char buf[128];  // 缓冲区
    // 连接服务器
	connect(fd, (struct sockaddr*)&saddr, sizeof(struct sockaddr_in));
	while (1) {
		rlen = read(0, buf, sizeof(buf)); // 读取输入内容
		buf[rlen]='\0';
		write(fd, buf, rlen+1);     // 发送
	}
    return 0;
}
