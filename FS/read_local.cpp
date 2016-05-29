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

double read_seq(const char *file, void *buf) {
    int fd = open(file, O_RDONLY | O_SYNC);
    if(fcntl(fd, F_NOCACHE, 1) == -1) {
        cout << "Can't disable cache" << endl;
    }

    uint64_t st;
    uint64_t ed;
    uint64_t total_time = 0;

    while (true) {
        st = rdtscStart();
        ssize_t bytes = read(fd, buf, BLOCKSIZE); // return #byte when read successfully
        if (bytes <= 0) {
            break;
        }
        ed = rdtscEnd();
        total_time += ed - st;
    }

    close(fd);
    double num = FILESIZE / BLOCKSIZE;
    return total_time / num / (2.7*1000);
}

double read_rand(const char *file, void *buf) {
    int i = 0;
    int fd = open(file, O_RDONLY | O_SYNC);
    if(fcntl(fd, F_NOCACHE, 1) == -1) {
        cout << "Can't disable cache" << endl;
    }
    off_t num = FILESIZE / BLOCKSIZE;

    uint64_t st;
    uint64_t ed;
    uint64_t total_time = 0;
    int count = 0;

    for (i = 0; i < num; i++) {
        off_t k = rand() % num;
        st = rdtscStart();
        lseek(fd, k * BLOCKSIZE, SEEK_SET); // offset
        read(fd, buf, BLOCKSIZE);
        ed = rdtscEnd();
        total_time += ed - st;
    }
    close(fd);
    double num1 = FILESIZE / BLOCKSIZE;
    return total_time / num1 / (2.7 * 1000);
}

/**
 * input the filesize and name of file
 */
int main(int argc, const char *argv[]) {
    FILESIZE = atoll(argv[1]) * 1024 * 1024; // in MB
    srand((unsigned int)time(NULL));
    void *buf = malloc(BLOCKSIZE);

    double seq_ans = read_seq(argv[2], buf);
    printf("%.2lf\n", seq_ans);
    free(buf);
    double rand_ans = read_rand(argv[2], buf);
    printf("%.2lf\n", rand_ans);
    return 0;
}
