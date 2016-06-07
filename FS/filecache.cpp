//
// Created by MuyBien on 5/27/16.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <chrono>
#include <iostream>

#define KB 1024
#define MB (1024*1024)
#define GB (1024*1024*1024)

using namespace std::chrono;

const off_t BLOCKSIZE = 4*1024;


int main(int argc, const char * argv[])
{
    std::cout<< "started" << std::endl;
    void* buf = malloc(BLOCKSIZE);
    int fd = open(argv[1], O_RDONLY | O_SYNC);
    const ssize_t FILESIZE = atoll(argv[2]) * 1024 * 1024;


    while(read(fd, buf, BLOCKSIZE) != 0){}
    close(fd);

    //We close the file and read it again
    fd = open(argv[1], O_RDONLY | O_SYNC);

    double bytesRead = 0;
    double total_time = 0;

    while(true){
        auto start = steady_clock::now();

        ssize_t bytes = read(fd, buf, BLOCKSIZE);
        bytesRead += bytes;
        auto end = steady_clock::now();
        duration<double> elapsed_seconds = end-start;
        total_time += elapsed_seconds.count();

        if (bytes <= 0 || bytesRead >= FILESIZE)
            break;
    }

    std::cout << total_time << std::endl;
    close(fd);
    free(buf);
    double result = FILESIZE / MB / total_time;
    printf("overall transfer rate: %lf MB/s\n", result);
    return 0;
}

