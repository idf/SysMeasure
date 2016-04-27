//
// Created by Danyang Zhang on 26/04/2016.
//

#include <cstdio>
#include <iostream>
#include "../lib/rdtscp.h"
#include "../common.h"

using namespace std;

int* cache_demo() {
    // https://gcc.gnu.org/onlinedocs/gcc-3.4.4/gcc/Optimize-Options.html
    int sz = 40960;
    int* A;
    A = (int *) malloc(sz * sizeof(int));

    int* p = A;
    cout << "size of int: " << sizeof(int) << endl;
    for(auto k = 1; k <= 2048; k *= 2) {
        p[0] = 0;
        uint64_t start = rdtscStart();
        p[k] *= 2;
        p[2*k] *= 2;
        p[3*k] *= 2;
        p[4*k] *= 2;
        p[5*k] *= 2;
        p[6*k] *= 2;
        p[7*k] *= 2;
        p[8*k] *= 2;
        uint64_t end = rdtscEnd();

        cout << k << "\t";
        cout << float (end - start) << endl;

        p = A;
    }
    return p;
}


int ** latency(long sz, long itr_cnt) {
    cout << "Test Memory Read Latency" << endl;
    int** A = new int* [sz];
    int ** ret = NULL ;
    for(auto k = 1; k <= 2048; k *= 2) {
        for(auto i = 0; i< sz; i++) {
            int index = (i/k+1)*k+rand()%k;
            index %= sz;
            A[i] = (int *) &A[index];
        }

        int ** p = A;
        int one_pass_cnt = sz/k + 1;
        uint64_t start = rdtscStart();
        for(auto i=0; i < itr_cnt; i++) {
            for(auto j=0; j < one_pass_cnt; j++) {
                p = (int **) *p;
            }
            p = A;
        }
        uint64_t end = rdtscEnd();
        ret = p;
        cout << k << "\t";
        cout << float (end - start) / (itr_cnt * one_pass_cnt) << endl;
    }
    return ret;
}

int main() {
    const bool DEBUG = true;

    if (!DEBUG) {
        freopen("Mem/result/output.txt","w", stdout);
    }

    // cout << cache_demo();
    cout << latency(409600, 1000);
}
