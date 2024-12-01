#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <iostream>

class ThreadPool {
   public:
    ThreadPool(int workerNum);  // 线程池构造函数
    ~ThreadPool();              // 线程池析构函数
    int makeWorker();           // 创建工人函数
   public:
    worker tidArr;          // 记录所有的子线程信息
    taskQueue taskQueue;    // 任务队列
    pthread_mutex_t mutex;  // 锁
    pthread_cond_t cond;    // 条件变量
    int exitFlag;           // 线程池是否销毁
};

#endif  // THREADPOOL_H