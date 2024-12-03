#ifndef TASKQUEUE_H
#define TASKQUEUE_H

#include <iostream>
// 队列节点
typedef struct node_s {
    int netfd;
    struct node_s* pNext;
} node_t;

class TaskQueue {
   public:
    TaskQueue();             // 构造任务队列函数
    ~TaskQueue();            // 析构任务队列函数
    int enQueue(int netfd);  // 任务入队函数
    int deQueue();           // 任务出队函数
   public:
    int queueSize;   // 任务队列大小
    node_t* pFront;  // 队头
    node_t* pRear;   // 队尾
};
#endif  // TASKQUEUE_H