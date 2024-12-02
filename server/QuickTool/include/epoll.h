#ifndef _EPPOLL_H_
#define _EPPOLL_H_

int epollAdd(int epfd, int fd); // 添加文件描述符到epoll监听树
int epollDel(int epfd, int fd); // 删除文件描述符从epoll监听树

#endif  // _EPPOLL_H_