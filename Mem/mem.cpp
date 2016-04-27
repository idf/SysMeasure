//
// Created by Danyang Zhang on 26/04/2016.
//

#include <cstdio>
#include <iostream>
#include "../lib/rdtscp.h"
#include "../common.h"

using namespace std;

void cache_demo() {
    // https://gcc.gnu.org/onlinedocs/gcc-3.4.4/gcc/Optimize-Options.html
    int sz = 40960;
    cout << "size of int: " << sizeof(int) << endl;
    for(auto k = 1; k <= 2048; k *= 2) {
        int *A;
        A = (int *) malloc(sz * sizeof(int));

        A[0] = 0;
        uint64_t start = rdtscStart();
        A[k] *= 2;
        A[2*k] *= 2;
        A[3*k] *= 2;
        A[4*k] *= 2;
        A[5*k] *= 2;
        A[6*k] *= 2;
        A[7*k] *= 2;
        A[8*k] *= 2;
        uint64_t end = rdtscEnd();

        cout << k << "\t";
        cout << float (end - start) << endl;

        free(A);
    }
}


int ** latency(long sz) {
    cout << "Test Memory Read Latency" << endl;
    int** A = new int* [sz];
    int ** ret = NULL ;
    for(auto k = 1; k <= 2048; k *= 2) {
        int ** p = A;
        for(auto i = 0; i< sz; i++) {
            int index = (i/k+1)*k+rand()%k;
            index %= sz;
            A[i] = (int *) &A[index];
        }

        uint64_t start = rdtscStart();
        for(auto i=0; i < sz; i++) {
            p = (int **) *p;
        }
        uint64_t end = rdtscEnd();
        ret = p;
        cout << k << "\t";
        cout << float (end - start)/sz << endl;
    }
    return ret;
}

int main() {
    const bool DEBUG = true;

    if (!DEBUG) {
        freopen("CPU/result/output.txt","w", stdout);
    }
    cache_demo();
    latency();
}
