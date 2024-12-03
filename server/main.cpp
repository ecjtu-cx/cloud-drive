#include <fmt/color.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

#include <csignal>

#include "checkError.h"
#include "epoll.h"
#include "tcpInit.h"
#include "threadPool.h"
int exitPipe[2];

void handler(int signum) {
    fmt::print(fmt::fg(fmt::color::yellow), "signum = {}\n", signum);
    write(exitPipe[1], "1", 1);
}

int main(int argc, char* argv[]) {
    ARGS_CHECK(argc, 4)

    // 父进程负责管理退出
    pipe(exitPipe);
    if (fork() != 0) {
        close(exitPipe[0]);
        signal(SIGUSR1, handler);
        wait(NULL);
        fmt::print(fmt::fg(fmt::color::yellow), "Parent is going to exit!\n");
        exit(0);
    }

    // 子进程创建线程池
    close(exitPipe[1]);
    ThreadPool threadPool(atoi(argv[3]));
    threadPool.makeWorker();
    // 初始化tcp连接
    int sockfd;
    tcpInit(argv[1], argv[2], &sockfd);
    // 初始化epoll监听
    int epfd = epoll_create(1);
    epollAdd(epfd, sockfd);
    epollAdd(epfd, exitPipe[0]);

    while(1){
        struct epoll_event readySet[1024];
        int readyNum = epoll_wait(epfd, readySet, 1024, -1);
        for(int i = 0; i < readyNum; ++ i){
            if(readySet[i].data.fd == sockfd){
                int netfd = accept(sockfd, NULL, NULL);
                fmt::print(fmt::fg(fmt::color::green), "I got a task\n");
                // 分配任务
                pthread_mutex_lock(&threadPool.mutex);
                threadPool.taskQueue.enQueue(netfd);
                fmt::print(fmt::fg(fmt::color::green), "I am master, I send a netfd {}\n", netfd);
                pthread_cond_signal(&threadPool.cond);
                pthread_mutex_unlock(&threadPool.mutex);
            }
            else if(readySet[i].data.fd == exitPipe[0]){
                // 线程池收到信号
                fmt::print(fmt::fg(fmt::color::green_yellow), "treadPool is going to exit!\n");
                pthread_mutex_lock(&threadPool.mutex);
                threadPool.exitFlag = 1;
                pthread_cond_broadcast(&threadPool.cond);
                pthread_mutex_unlock(&threadPool.mutex);
                for(int j = 0; j < threadPool.tidArr.workerNum; ++j){
                    pthread_join(threadPool.tidArr.threadArr[j], NULL);
                }
                fmt::print(fmt::fg(fmt::color::yellow), "main thread is going to exit!\n");
                exit(0);
            }
        }
    }
    return 0;
}