#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int tcp_connect(int af, char *servip, unsigned short port) {
        struct sockaddr_in servaddr;
        int  s;
        // 소켓 생성
        if ((s = socket(af, SOCK_STREAM, 0)) < 0)
                return -1;
        // 채팅 서버의 소켓주소 구조체 servaddr 초기화
        bzero((char *)&servaddr, sizeof(servaddr));
        servaddr.sin_family = af;
        inet_pton(AF_INET, servip, &servaddr.sin_addr);
        servaddr.sin_port = htons(port);

        // 연결요청
        if (connect(s, (struct sockaddr *)&servaddr, sizeof(servaddr))
                < 0)
                return -1;
        return s;
}
