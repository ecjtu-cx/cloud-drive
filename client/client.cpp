#include <my.h>

typedef struct train_s {
    int length;       // 火车头
    char data[1000];  // 火车车厢
} train_t;

int recvn(int sockfd, void *buf, long total) {
    char *p = (char *)buf;
    long cursize = 0;
    while (cursize < total) {
        ssize_t sret = recv(sockfd, p + cursize, total - cursize, 0);
        if (sret == 0) {
            return 1;
        }
        cursize += sret;
    }
    return 0;
}
int recvFile(int sockfd) {
    char filename[4096] = {0};
    train_t train;
    // 先收火车头，以知道车厢实际长度
    recvn(sockfd, &train.length, sizeof(train.length));
    recvn(sockfd, train.data, train.length);
    memcpy(filename, train.data, train.length);
    off_t filesize;
    recvn(sockfd, &train.length, sizeof(train.length));
    recvn(sockfd, train.data, train.length);
    memcpy(&filesize, train.data, train.length);
    printf("filesize = %ld\n", filesize);
    int fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
    ftruncate(fd, filesize);  // 先修改文件大小
    char *p =
        (char *)mmap(NULL, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    ERROR_CHECK(p, MAP_FAILED, "mmap");
    recvn(sockfd, p, filesize);
    munmap(p, filesize);
    close(fd);
    return 0;
}
int main(int argc, char *argv[]) {
    
    ARGS_CHECK(argc, 3);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[2]));
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
    int ret =
        connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    ERROR_CHECK(ret, -1, "connect");
    recvFile(sockfd);
    close(sockfd);
    return 0;
}