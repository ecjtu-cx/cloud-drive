#include "threadPool.h"

#include "worker.h"

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
        pthread_create(&tidArr.threadArr[i], NULL, tidArr.threadFunc, (void*)this);
    }
    return 0;
}