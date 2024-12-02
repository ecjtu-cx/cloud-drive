#include "transFile.h"

#include <arpa/inet.h>
#include <fcntl.h>
#include <fmt/color.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <unistd.h>

int transFile(int netfd, string filename) {
    const char* ctypeFilename = filename.c_str();
    // 组装小火车
    train_t train;
    train.length = filename.size();
    memcpy(train.data, ctypeFilename, train.length);
    // 发送小火车 头长度+车厢长度
    send(netfd, &train, sizeof(train.length) + train.length, MSG_NOSIGNAL);
    // 发送文件
    struct stat statbuf;
    int fd = open(ctypeFilename, O_RDWR);  // open 必须用O_RDWR
    fstat(fd, &statbuf);
    train.length = sizeof(off_t);
    memcpy(train.data, &statbuf.st_size, train.length);
    send(netfd, &train, sizeof(train.length) + train.length, MSG_NOSIGNAL);
    sleep(10);
    fmt::print(fmt::fg(fmt::color::yellow), "transfile done\n");
    sendfile(netfd, fd, NULL, statbuf.st_size);
    close(fd);

    return 0;
}