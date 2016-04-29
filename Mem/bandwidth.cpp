//
// Created by MuyBien on 4/27/16.
//

#include <iostream>
#include <assert.h>
#include <chrono>
#include <immintrin.h>
#include "../common.h"

#ifdef __AVX__
#include <immintrin.h>
#endif

using namespace std;

#define MB (1024*1024LL)
#define GB (1024*1024*1024LL)
#define SIZE (1*GB)
#define EXPERIMENT 1
#define REPETITION 20

typedef __int128_t TYPE;
//typedef long long TYPE;
//typedef int TYPE;
//typedef char TYPE;


TYPE data[SIZE/sizeof(TYPE)] __attribute__((aligned (32)));

double calculate_bandwidth(double size, double seconds){
    return size / seconds;
}

void read_memory_loop(){
    TYPE val = 0;
    int bound = SIZE / sizeof(TYPE);
    for(int i=0; i<bound; i++){
        val = data[i];
    }
    // make use of val to prevent compiler optimization
    assert(!(val==0));
}

void read_memory_loop_unroll(){
    TYPE val = 0;
    int bound = SIZE / sizeof(TYPE);
    for(int i=0; i<bound; i=i+8){
        val = data[i];
        val = data[i+1];
        val = data[i+2];
        val = data[i+3];
        val = data[i+4];
        val = data[i+5];
        val = data[i+6];
        val = data[i+7];

    }
    // make use of val to prevent compiler optimization
    assert(!(val==0));
}

void read_memory_loop_experiment(){
    cout << "====== read memory loop experiment ======" <<endl;
//    for(int i=0; i<EXPERIMENT; i++){
//        cout << "Experiment #" << i << ":" << endl;

        double min_duration = 0;
        for(int j=0; j<REPETITION; j++){
            auto start = chrono::steady_clock::now();
            read_memory_loop();
            auto end = chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
//            cout << elapsed_seconds.count() << endl;
            if(j==0) min_duration = elapsed_seconds.count();
            else min_duration = min(min_duration, elapsed_seconds.count());
        }
        cout << calculate_bandwidth((double) SIZE / GB, min_duration) << endl;
//    }
}

void read_memory_loop_unroll_experiment(){
    cout << "====== read memory loop unroll experiment ======" <<endl;
//    for(int i=0; i<EXPERIMENT; i++){
//        cout << "Experiment #" << i << ":" << endl;

    double min_duration = 0;
    for(int j=0; j<REPETITION; j++){
        auto start = chrono::steady_clock::now();
        read_memory_loop_unroll();
        auto end = chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
//            cout << elapsed_seconds.count() << endl;
        if(j==0) min_duration = elapsed_seconds.count();
        else min_duration = min(min_duration, elapsed_seconds.count());
    }
    cout << calculate_bandwidth((double) SIZE / GB, min_duration) << endl;
//    }
}

__attribute__ ((target ("sse4.2")))
__attribute__ ((target ("xsave")))
__m256 read_memory_avx() {
    __m256* varray = (__m256*) data;

    __m256 accum = _mm256_set1_ps((float)  0x00000000);
    for (int i = 0; i < SIZE/sizeof(__m256i); i++) {
        accum = _mm256_add_ps(varray[i], accum);
    }

    assert(!_mm256_testz_ps(accum, accum));
    return accum;
}

void read_memory_avx_experiment(){
    cout << "====== read memory avx experiment ======" <<endl;
//    for(int i=0; i<EXPERIMENT; i++){
//        cout << "Experiment #" << i << ":" << endl;

        double min_duration = 0;
        for(int j=0; j<REPETITION; j++){
            auto start = chrono::steady_clock::now();
            read_memory_avx();
            auto end = chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            if(j==0) min_duration = elapsed_seconds.count();
            else min_duration = min(min_duration, elapsed_seconds.count());
        }
        cout << calculate_bandwidth((double) SIZE / GB, min_duration) <<endl;
//    }
}

void write_memory_loop(){
    TYPE val = 0;
    int bound = SIZE/sizeof(TYPE);
    for(int i=0; i<bound; i++){
        data[i] = 0;
    }
    // make use of val to prevent compiler optimization
    assert(val==0);
}

void write_memory_loop_experiment(){
    cout << "====== write memory loop experiment ======" <<endl;

//    for(int i=0; i<EXPERIMENT; i++){
//        cout << "Experiment #" << i << ":" << endl;
    double min_duration = 0;
    for(int j=0; j<REPETITION; j++){
        auto start = chrono::steady_clock::now();
        write_memory_loop();
        auto end = chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        if(j==0) min_duration = elapsed_seconds.count();
        else min_duration = min(min_duration, elapsed_seconds.count());
    }
    cout << calculate_bandwidth((double) SIZE / GB, min_duration) <<endl;
//    }
}

void write_memory_loop_unroll(){
    TYPE val = 0;
    int bound = SIZE/sizeof(TYPE);
    for(int i=0; i<bound; i = i+8){
        data[i] = 0;
        data[i+1] = 0;
        data[i+2] = 0;
        data[i+3] = 0;
        data[i+4] = 0;
        data[i+5] = 0;
        data[i+6] = 0;
        data[i+7] = 0;
    }
    // make use of val to prevent compiler optimization
    assert(val==0);
}

void write_memory_loop_unroll_experiment(){
    cout << "====== write memory loop unroll experiment ======" <<endl;

//    for(int i=0; i<EXPERIMENT; i++){
//        cout << "Experiment #" << i << ":" << endl;
    double min_duration = 0;
    for(int j=0; j<REPETITION; j++){
        auto start = chrono::steady_clock::now();
        write_memory_loop_unroll();
        auto end = chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        if(j==0) min_duration = elapsed_seconds.count();
        else min_duration = min(min_duration, elapsed_seconds.count());
    }
    cout << calculate_bandwidth((double) SIZE / GB, min_duration) <<endl;
//    }
}


void write_memory_repeated_string_experiment(){
    cout << "====== write memory repeated string experiment ======" <<endl;
//    for(int i=0; i<EXPERIMENT; i++){
//        cout << "Experiment #" << i << ":" << endl;

    double min_duration = 0;
    for(int j=0; j<REPETITION; j++){
        auto start = chrono::steady_clock::now();

        // repeated string operations in assembly code
        // repeatedly store a word into an array
        asm("cld\n"
                "rep stosq"
        : : "D" (data), "c" (SIZE / 8), "a" (0) );

        auto end = chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        if(j==0) min_duration = elapsed_seconds.count();
        else min_duration = min(min_duration, elapsed_seconds.count());

//        cout << elapsed_seconds.count() << endl;
    }
    cout << calculate_bandwidth((double) SIZE / GB, min_duration) <<endl;
//    }
}

void write_memory_memset_experiment(){
    cout << "====== write memory memset experiment ======" <<endl;
//    for(int i=0; i<EXPERIMENT; i++){
//        cout << "Experiment #" << i << ":" << endl;

        double min_duration = 0;
        for(int j=0; j<REPETITION; j++){
            auto start = chrono::steady_clock::now();
            memset(data, 0, SIZE);
            auto end = chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            if(j==0) min_duration = elapsed_seconds.count();
            else min_duration = min(min_duration, elapsed_seconds.count());
        }
        cout << calculate_bandwidth((double) SIZE / GB, min_duration) <<endl;
//    }
}


int main(){
    memset(data, 0xFF, SIZE);

    cout << "data array size is: " << sizeof(data) << " bytes " << endl;
//    cout << sizeof(__int128_t) <<endl;
//    cout << sizeof(long long ) <<endl;
//    cout << sizeof(uint64_t) << endl;

    read_memory_loop_experiment();
    read_memory_loop_unroll_experiment();
    read_memory_avx_experiment();
    write_memory_loop_experiment();
    write_memory_loop_unroll_experiment();
    write_memory_memset_experiment();
    write_memory_repeated_string_experiment();
}

