//
// Created by Danyang Zhang on 27/05/2016.
//

#include <iostream>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include "../common.h"
#include <time.h>
#include <fcntl.h>
#include <string>

using namespace std;

const off_t BLOCKSIZE = 4*1024;
off_t FILESIZE;

double avg_seq_time(string file, void* buf) {
    int fd = open(file, O_RDONLY | O_SYNC);
    if(fcntl(fd, F_NOCACHE, 1) == -1) {
        cout << "Can't open file" << endl;
    }
    uint64_t st;
    uint64_t ed;
    uint64_t total_time;
    int count = 0;

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
    return total_time / num / 2.6 / 1000;
}

double avg_random_time(string file, void* buf) {
    int i = 0;
    int fd = open(file, O_RDONLY | O_SYNC); //open synchronously
    if(fcntl(fd, F_NOCACHE, 1) == -1) {
        //disable cache
        cout << "Can't open file" << endl; //cannot disable cache
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
    return total_time / (double)num / 2.6 / 1000;
}

/**
 * input the filesize and name of file
 */
int main(int argc, const char *argv[]) {
    FILESIZE = atoll(argv[1]);
    srand((unsigned int)time(NULL));
    void *buf = malloc(BLOCKSIZE);

    double seq_ans = avg_seq_time(argv[2], buf);
    printf("%.2lf\n", seq_ans);
    free(buf);
    // double ran_ans = avg_random_time(argv[2], buf);
    free(buf);
    return 0;
}
