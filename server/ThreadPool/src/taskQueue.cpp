#include <taskQueue.h>
#include <fmt/core.h>
#include <fmt/color.h>
// 构造任务队列函数
TaskQueue::TaskQueue() {
    pFront = pRear = nullptr;
    queueSize = 0;
}
// 析构任务队列函数
TaskQueue::~TaskQueue() {
    while(queueSize > 0){
        deQueue();
    }
}
// 任务入队函数
int TaskQueue::enQueue(int netfd){
    node_t * pNew = new node_t;
    pNew->netfd = netfd;
    pNew->pNext = nullptr;
    if(queueSize == 0){
        pFront = pRear = pNew;
    } else {
        pRear->pNext = pNew;
        pRear = pNew;
    }
    ++queueSize;
    return 0;
}
// 任务出队函数
int TaskQueue::deQueue(){
    if(queueSize == 0){
        fmt::print(fmt::fg(fmt::color::red), "Task queue is empty!\n");
        return -1;
    }
    node_t * pDel = pFront;
    pFront = pFront->pNext;
    delete pDel;
    --queueSize;
    return 0;
}