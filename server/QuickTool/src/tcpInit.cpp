#include "tcpInit.h"

#include <arpa/inet.h>

#include <iostream>

#include "checkError.h"

// 初始化tcp服务器
int tcpInit(const char *ip, const char *port, int *psockfd) {
    // socket setsockopt bind listen
    *psockfd = socket(AF_INET, SOCK_STREAM, 0);
    int reuse = 1;
    int ret =
        setsockopt(*psockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    ERROR_CHECK(ret, -1, "setsockopt");
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(port));
    addr.sin_addr.s_addr = inet_addr(ip);
    ret = bind(*psockfd, (struct sockaddr *)&addr, sizeof(addr));
    ERROR_CHECK(ret, -1, "bind");
    listen(*psockfd, 50);
    return 0;
}