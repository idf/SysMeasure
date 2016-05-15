//
// Created by Danyang Zhang on 28/04/2016.
//


#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <iostream>
#include <complex>
using namespace std;

#define TARGET_FILE "./test"


const long long FILESIZE = 1024*1024*1024; // per GB file
const int MS = 1000;

void pageFault() {
    int targetFile = open(TARGET_FILE, O_RDWR);
    if(targetFile < 0) {
        cout << "Unable to open the target file." << endl;
        return;
    }

    const int PAGESIZE = getpagesize();

    // double overhead = getReadOverhead();

    for(int page_stride = 1; page_stride <= 65536; page_stride *= 4) {  // 4^8 = 65536
        system("purge");  // clear cache

        cout << "page stride: " << page_stride << endl;
        int byte_stride = page_stride * PAGESIZE; // 4194304 bytes = 4MB
        int EXPERIMENT_CNT = min<int>(100, FILESIZE / byte_stride);

        // mmap: map file to memory
        char* map = (char*) mmap(NULL, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, targetFile, 0);
        char targetByte;
        double total = 0;
        for(int j = 0; j < EXPERIMENT_CNT; j++) {
            uint64_t index = min<int>((j * byte_stride + rand() % byte_stride), FILESIZE - 1);  // rand() for preventing caching
            auto start = chrono::steady_clock::now();
            targetByte = map[index];
            auto end = chrono::steady_clock::now();
            chrono::duration<double> diff = end-start;
            total += diff.count()*MS;
            cout << diff.count()*MS << endl;
        }

        double average = total / EXPERIMENT_CNT;
        cout << "Avg time for page stride size = " << page_stride << " in millisecond is "<< average << endl;
        munmap(map, FILESIZE);
        cout << page_stride << " pages stride" << endl;
        cout << targetByte;
    }
    close(targetFile);
    return;
}

void createFile() {
    FILE *fp=fopen(TARGET_FILE, "w");
    ftruncate(fileno(fp), FILESIZE);
    fclose(fp);
}

int main() {
    createFile();
    pageFault();
}