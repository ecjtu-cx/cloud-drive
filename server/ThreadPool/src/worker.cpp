#include "worker.h"
#include "taskQueue.h"
#include "threadPool.h"
#include <fmt/core.h>
#include <fmt/color.h>
#include <unistd.h>
#include "transFile.h"
// 工人构造函数
worker::worker(int workerNum){
    this->workerNum = workerNum;
    this->threadArr = new pthread_t[workerNum];
}
// 工人析构函数
worker::~worker(){
    delete [] threadArr;
}
// 工人工作函数
void * worker::threadFunc(void * arg){
    ThreadPool * pThreadPool = (ThreadPool *) arg;
    fmt::print(fmt::fg(fmt::color::green), "Thread {} is created\n", pthread_self());
    while(1){
        fmt::print(fmt::fg(fmt::color::green), "Thread {} is waiting for task\n", pthread_self());
        pthread_mutex_lock(&pThreadPool->mutex);
        int netfd;
        while(pThreadPool->exitFlag == 0 && pThreadPool->taskQueue.queueSize <= 0){
            pthread_cond_wait(&pThreadPool->cond, &pThreadPool->mutex);
        }
        if(pThreadPool->exitFlag == 1){
            fmt::print(fmt::fg(fmt::color::yellow), "Thread {} exit!\n", pthread_self());
            pthread_mutex_unlock(&pThreadPool->mutex);
            pthread_exit(NULL);
        }
        netfd = pThreadPool->taskQueue.pFront->netfd;
        fmt::print(fmt::fg(fmt::color::green), "Thread {} get task: {}\n", pthread_self(), netfd);
        pThreadPool->taskQueue.deQueue();
        pthread_mutex_unlock(&pThreadPool->mutex);
        //TODO: 业务处理
        transFile(netfd, "../test.txt"); 
        close(netfd);
    }
}