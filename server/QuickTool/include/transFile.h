#ifndef _TRANSFILE_H_
#define _TRANSFILE_H_
#include <iostream>

using std::string;

typedef struct train_s {
    int length;       // 火车车厢大小
    char data[1000];  // 火车车厢
} train_t;

int transFile(int netfd, string tempFilename);  // 传输文件函数

#endif _TRANSFILE_H_  // _TRANSFILE_H_