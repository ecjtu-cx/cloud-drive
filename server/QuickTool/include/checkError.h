#ifndef CHECKERROR_H
#define CHECKERROR_H

#include <stdio.h>
// 检查传入参数个数是否正确
#define ARGS_CHECK(argc, num)                 \
    {                                         \
        if (argc != num) {                    \
            fprintf(stderr, "args error!\n"); \
            return -1;                        \
        }                                     \
    }
// 检查系统调用返回值是否为-1，若是则输出错误信息并返回-1
#define ERROR_CHECK(ret, num, msg) \
    {                              \
        if (ret == num) {          \
            perror(msg);           \
            return -1;             \
        }                          \
    }
// 线程错误检查
#define THREAD_ERROR_CHECK(ret, msg)                      \
    {                                                     \
        if (ret != 0) {                                   \
            fprintf(stderr, "%s:%s", msg, strerror(ret)); \
        }                                                 \
    }
#endif  // CHECKERROR_H