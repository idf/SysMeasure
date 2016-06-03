//
// Created by MuyBien on 5/28/16.
//

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <chrono>

#define FileDir "contentionTestFile/"
#define FilePrefix FileDir "contention_"
#define ExperimentTimes 20
#define FileNumber 16
#define MB (1024*1024)
#define BlockSize 4096

#define DataSequentialRead "result_sequential_contention.txt"
#define DataRandomRead "result_random_contention.txt"
#define DataSequentialReadMixed "result_sequential_contention_mixed.txt"
#define DataRandomReadMixed "result_random_contention_mixed.txt"

using namespace std;

const int FileSize = 4 * MB;
const int BlockNumber = FileSize / BlockSize;

void readFile(int t, bool isSequential) {
//    cout << "start child process #" << t <<endl;
    string path(FilePrefix + to_string(t) + ".txt");
    char *fileName = &path[0];

    int fd;
    void *buf = malloc(BlockSize);
    for (int i = 0; i < ExperimentTimes * 2; i++) {
        fd = open(fileName, O_RDONLY | O_SYNC);

        if (fd < 0) {
            cout << "cannot open file #" << t << endl;
            return;
        }
        if (fcntl(fd, F_NOCACHE, 1) < 0) {
            cout << "cannot close file cache for file #" << t << endl;
            return;
        }

        if(isSequential) {
            for (int j = 0; j < BlockNumber; j++) {
                read(fd, buf, BlockSize);
            }
        }
        else{
            size_t offset;
            for(int i = 0; i < BlockNumber; i++) {
                offset = rand() % BlockNumber;
                // using lseek to set offset
                lseek(fd, offset, SEEK_SET);
                read(fd, buf, BlockSize);
            }
        }

//        cout << "finish reading file #"<< t << endl;
        close(fd);

    }
    free(buf);
}

void readFileTest(bool isSequential, bool oddIsSeq, bool evenIsSeq){
    int fd;

    char* fileName = FilePrefix "0.txt";
    void* buf = malloc(BlockSize);
    pid_t pids[FileNumber];

    for(int f=0; f<FileNumber; f++) {

        cout << "=== " << f << " processes ===" << endl;
        for(int t=1; t<=f; t++){
            pids[t] = fork();
            if(pids[t] < 0){
                cout << "cannot fork a process #" << t << endl;
                abort();
            }
            // child process
            else if(pids[t] == 0){
                if(t%2==0) readFile(t, evenIsSeq);
                else readFile(t, oddIsSeq);
                exit(0);
            }
        }


        for (int i = 0; i < ExperimentTimes; i++) {
            fd = open(fileName, O_RDONLY | O_SYNC);
            if (fd < 0) {
                cout << "cannot open file 0" << endl;
                return;
            }
            if (fcntl(fd, F_NOCACHE, 1) < 0) {
                cout << "cannot close file cache for file 0" << endl;
                return;
            }

            double total_time = 0;

            if (isSequential) {
                for (int j = 0; j < BlockNumber; j++) {
                    auto start = chrono::steady_clock::now();

                    read(fd, buf, BlockSize);

                    auto end = chrono::steady_clock::now();
                    chrono::duration<double> elapsed_seconds = end - start;
                    total_time += elapsed_seconds.count();
                }
            }
            else{
                size_t offset;
                for(int i = 0; i < BlockNumber; i++) {
                    offset = rand() % BlockNumber;
                    // using lseek to set offset
                    auto start = chrono::steady_clock::now();

                    lseek(fd, offset, SEEK_SET);
                    read(fd, buf, BlockSize);

                    auto end = chrono::steady_clock::now();
                    chrono::duration<double> elapsed_seconds = end - start;
                    total_time += elapsed_seconds.count();
                }
            }

            // time unit in ms
            cout << total_time / BlockNumber * 1000 << endl;
            close(fd);
        }

        wait(NULL);
        cout << endl;

    }
    free(buf);
    return;
}

int main(){
    std::streambuf *psbuf, *backup;
    backup = std::cout.rdbuf();     // back up cout's streambuf
    std::ofstream filestr;

    // 1. total sequential read
//    filestr.open(DataSequentialRead);
//    psbuf = filestr.rdbuf();        // get file's streambuf
//    std::cout.rdbuf(psbuf);         // assign streambuf to cout
//    readFileTest(true, true, true);
//    filestr.close();

    // 2. total random read
//    filestr.open(DataRandomRead);
//    psbuf = filestr.rdbuf();
//    std::cout.rdbuf(psbuf);
//    readFileTest(false, false, false);
//    filestr.close();

    // 3. sequential read + half-half mixed read
//    filestr.open(DataSequentialReadMixed);
//    psbuf = filestr.rdbuf();
//    std::cout.rdbuf(psbuf);
//    readFileTest(true, true, false);
//    filestr.close();


    // 4. random read + half-half mixed read
    filestr.open(DataRandomReadMixed);
    psbuf = filestr.rdbuf();
    std::cout.rdbuf(psbuf);
    readFileTest(false, true, false);
    filestr.close();

    std::cout.rdbuf(backup);        // restore cout's original streambuf
    return 0;

}

