#ifndef WORKER_H
#define WORKER_H

#include <pthread.h>

class worker {
   public:
    worker(int workerNum);        // 工人构造函数
    ~worker();                    // 工人析构函数
    static void* threadFunc(void* arg);  // 工人工作函数
   public:
    pthread_t* threadArr;  // 线程数组
    int workerNum;         // 工人数量
};

#endif  // WORKER_H