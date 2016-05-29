//
// Created by Danyang Zhang on 27/05/2016.
//

#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <chrono>
#include <stdlib.h>
#include <unistd.h>
#include "../common.h"
#include <time.h>
#include <fcntl.h>
#include <string>

using namespace std;
const off_t BLOCKSIZE = 4*1024;
off_t FILESIZE;   // in MB

double measure(const char *file, void *buf, uint64_t (*f)(int, void*)) {
    int fd = open(file, O_RDONLY | O_SYNC);
    if(fcntl(fd, F_NOCACHE, 1) == -1) {
        cout << "Can't disable cache" << endl;
    }
    uint64_t totalTime = (*f)(fd, buf);
    close(fd);
    double num = FILESIZE / BLOCKSIZE;
    return totalTime / num / (2.7*1000);
}

uint64_t read_seq(int fd, void* buf) {
    uint64_t st;
    uint64_t ed;
    uint64_t totalTime = 0;
    while (true) {
        st = rdtscStart();
        ssize_t bytes = read(fd, buf, BLOCKSIZE); // return #byte when read successfully
        if (bytes <= 0) {
            break;
        }
        ed = rdtscEnd();
        totalTime += ed - st;
    }
    return totalTime;
}

uint64_t read_rand(int fd, void* buf) {
    uint64_t st;
    uint64_t ed;
    uint64_t totalTime = 0;
    off_t blockCnt = FILESIZE / BLOCKSIZE;
    for (int i = 0; i < blockCnt; i++) {
        off_t k = rand() % blockCnt;
        st = rdtscStart();
        lseek(fd, k * BLOCKSIZE, SEEK_SET); // offset
        read(fd, buf, BLOCKSIZE);
        ed = rdtscEnd();
        totalTime += ed - st;
    }
    return totalTime;
}

/**
 * "Please supply two arguments: file size in MB; file path"
 */
int main(int argc, const char *argv[]) {
    FILESIZE = atoll(argv[1]) * 1024 * 1024; // in MB
    cout << argv[1] << "MB" << endl;
    srand((unsigned int)time(NULL));
    void *buf = malloc(BLOCKSIZE);

    double seq_ans = measure(argv[2], buf, &read_seq);
    printf("%.2lf\n", seq_ans);
    free(buf);
    double rand_ans = measure(argv[2], buf, &read_rand);
    printf("%.2lf\n", rand_ans);
    return 0;
}
