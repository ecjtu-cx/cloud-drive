#include "threadPool.h"

#include "worker.h"
#include <fmt/color.h>

// 线程池构造函数
ThreadPool::ThreadPool(int workerNum) : tidArr(workerNum) {
    exitFlag = 0;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
}
// 线程池析构函数
ThreadPool::~ThreadPool() {
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}
// 创建工人函数
int ThreadPool::makeWorker(){
    for(int i = 0; i < tidArr.workerNum; i++){
        int ret = pthread_create(&tidArr.threadArr[i], NULL, tidArr.threadFunc, (void*)this);
        if (ret != 0) {
            fmt::print(fmt::fg(fmt::color::red), "Failed to create thread {}\n", i);
        }
    }
    return 0;
}