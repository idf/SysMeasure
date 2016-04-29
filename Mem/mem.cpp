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


int ** latency(long sz, long itr_cnt, bool random) {
    cout << "Test Memory Read Latency" << endl;
    int** A = new int* [sz];
    int ** ret = NULL ;
    for(auto k = 1; k <= 2048; k *= 2) {
        // construct the linked list using array
        for(auto i = 0; i< sz; i++) {
            int index;
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
        int one_pass_cnt = sz/k + 1;
        uint64_t start = rdtscStart();   // TODO use stedy_clock
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
    cout << latency(409600, 1000, true);
    cout << latency(409600, 1000, false);
}
