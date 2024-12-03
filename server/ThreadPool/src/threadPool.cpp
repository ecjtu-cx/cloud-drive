#include "threadPool.h"

#include <fmt/color.h>

#include "worker.h"

// 线程池构造函数
ThreadPool::ThreadPool(int workerNum) : tidArr(workerNum), taskQueue() {
    // fmt::print(fmt::fg(fmt::color::green), "debug");
    this->exitFlag = 0;
    pthread_mutex_init(&this->mutex, NULL);
    pthread_cond_init(&this->cond, NULL);
}
// 线程池析构函数
ThreadPool::~ThreadPool() {
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}
// 创建工人函数
int ThreadPool::makeWorker() {
    for (int i = 0; i < this->tidArr.workerNum; i++) {
        fmt::print(fmt::fg(fmt::color::green),
                   "I am master, I create a worker {}\n", i);
        int ret = pthread_create(&this->tidArr.threadArr[i], NULL,
                                 this->tidArr.threadFunc, (void*)this);
        if (ret != 0) {
            fmt::print(fmt::fg(fmt::color::red), "Failed to create thread {}\n",
                       i);
        }
    }
    return 0;
}