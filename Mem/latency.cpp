//
// Created by Danyang Zhang on 26/04/2016.
//

#include <cstdio>
#include <iostream>
#include "../common.h"

using namespace std;

int* cache_demo() {
    // https://gcc.gnu.org/onlinedocs/gcc-3.4.4/gcc/Optimize-Options.html
    int sz = 409600;
    int* A;
    A = (int *) malloc(sz * sizeof(int));

    int* p = A;
    cout << "size of int: " << sizeof(int) << endl;
    for(auto k = 1; k <= 4096; k *= 2) {
        p[0] = 0;
        uint64_t start = rdtscStart();
        for (auto i=1; i< 50; i++) {
            p[i*k] *= 2;
        }
        uint64_t end = rdtscEnd();

        cout << k << "\t";
        cout << float (end - start) << endl;

        p = A;
    }
    return p;
}


int ** latency(long sz, long k, long itr_cnt, bool random) {
    int ** ret = NULL ;

    int** A = new int* [sz];
    // construct the linked list using array
    for(auto i = 0; i < sz; i++) {
        uint64_t index;
        if (random) {
            index = (i/k+1)*k+rand()%k;
        }
        else {
            index = (i/k+1)*k;
        }

        index %= sz;
        A[i] = (int *) &A[index];
    }

    int ** p = A;
    uint64_t one_pass_cnt = sz/k + 1;
    long long start = rdtscStart();
    for(auto i=0; i < itr_cnt; i++) {
        for(auto j=0; j < one_pass_cnt; j++) {
            p = (int **) *p;
        }
    }
    long long end = rdtscEnd();
    free(A);
    ret = p;

    cout << k << "\t";
    cout << (float) (end - start) / (itr_cnt * one_pass_cnt) << endl;
    return ret;
}

int main() {
    const bool DEBUG = true;

    if (!DEBUG) {
        freopen("Mem/result/output.txt","w", stdout);
    }

    // cout << cache_demo();
    int sz1kb = 1024/4;
    for(auto sz = 16*sz1kb, i = 1; i <= 14; i++, sz *= 2) {
        cout << "Array size: " << sz << "x4Byte" << endl;
        for(auto k = 8; k < 4096; k *=4) {
            latency(sz, k, 100, true);
        }
    }
    // cout << latency(409600, 1000, false);
}
