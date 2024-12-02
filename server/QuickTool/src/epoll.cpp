#include "epoll.h"

#include <sys/epoll.h>
#include <unistd.h>
// 添加文件描述符到epoll监听树
int epollAdd(int epfd, int fd) {
    struct epoll_event events;
    events.events = EPOLLIN;
    events.data.fd = fd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &events);
    return 0;
}
// 删除文件描述符从epoll监听树
int epollDel(int epfd, int fd) {
    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
    return 0;
}