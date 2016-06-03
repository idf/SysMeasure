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

const int UNIT = 1024; // KB

const off_t BLOCKSIZE = 4 * UNIT;  // by UNIT
off_t FILESIZE;   // by UNIT
const int EXP = 10;
const double CPU_CLOCK_RATE = 2.7; // in GHz

vector<double> measure(const char *file, void *buf, uint64_t (*f)(int, void*)) {
    vector<double> rets;
    for (int t = 0; t < EXP; t++) {
        system("purge");
        int fd = open(file, O_RDONLY | O_SYNC);
        if(fcntl(fd, F_NOCACHE, 1) == -1) {
            cout << "Can't disable cache" << endl;
        }
        uint64_t totalTime = (*f)(fd, buf);
        close(fd);
        double num = FILESIZE / BLOCKSIZE;
        double ret = totalTime / num / (CPU_CLOCK_RATE*1000);  // micro second
        rets.push_back(ret);
    }
    stats(rets);
    return rets;
}

uint64_t read_seq(int fd, void* buf) {
    uint64_t start;
    uint64_t end;
    uint64_t totalTime = 0;
    while (true) {
        start = rdtscStart();
        ssize_t bytes = read(fd, buf, BLOCKSIZE);
        if (bytes <= 0) {
            break;
        }
        end = rdtscEnd();
        totalTime += end - start;
    }
    return totalTime;
}

uint64_t read_rand(int fd, void* buf) {
    uint64_t start;
    uint64_t end;
    uint64_t totalTime = 0;
    off_t blockCnt = FILESIZE / BLOCKSIZE;
    for (int i = 0; i < blockCnt; i++) {
        off_t k = rand() % blockCnt;
        start = rdtscStart();
        lseek(fd, k * BLOCKSIZE, SEEK_SET); // offset
        read(fd, buf, BLOCKSIZE);
        end = rdtscEnd();
        totalTime += end - start;
    }
    return totalTime;
}

/**
 * "Please supply two arguments: file size in MB; file path"
 */
int main(int argc, const char *argv[]) {
    FILESIZE = atoll(argv[1]) * UNIT; // in KB
    cout << argv[1] << "KB" << endl;

    srand((unsigned int)time(NULL));
    void *buf = malloc(BLOCKSIZE);
    cout << "Sequential read" << endl;
    measure(argv[2], buf, &read_seq);
    free(buf);
    cout << "Random read" << endl;
    measure(argv[2], buf, &read_rand);
    return 0;
}
