//
// Created by MuyBien on 4/16/16.
//

#ifndef SYSMEASURE_COMMON_H
#define SYSMEASURE_COMMON_H


#include <cstdint>
#include <cmath>
#include <numeric>
#include <vector>
#include <mach/mach_time.h>

using namespace std;

static inline uint64_t rdtscStart(void){
    uint32_t cycles_high, cycles_low;
    asm volatile (
            "CPUID\n\t" /*serialize*/
            "RDTSC\n\t" /*read the clock*/
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            : "=r" (cycles_high), "=r" (cycles_low):: "%rax", "%rbx", "%rcx", "%rdx", "memory"
    );
    return (((uint64_t) cycles_high << 32)| cycles_low);
}


static inline uint64_t rdtscEnd(void){
    uint32_t cycles_high, cycles_low;
    asm volatile (
            "RDTSCP\n\t" /*read the clock*/
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            "CPUID\n\t"
            : "=r" (cycles_high), "=r"(cycles_low):: "%rax", "%rbx", "%rcx", "%rdx", "memory"
    );
    return (((uint64_t)cycles_high << 32) | cycles_low);
}


static inline vector<double> stats(vector<double> v) {
    double sum = std::accumulate(v.begin(), v.end(), 0.0);
    double mean = sum / v.size();

    double sq_sum = std::inner_product(v.begin(), v.end(), v.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / v.size() - mean * mean);
    double min = *std::min_element(v.begin(), v.end());
    double max = *std::max_element(v.begin(), v.end());
    cout << "mean: " << mean << endl;
    cout << "stdev: " << stdev << endl;
    cout << "min: " << min << endl;
    cout << "max: " << max << endl;
    vector<double> ret;
    ret.push_back(mean);
    ret.push_back(stdev);
    ret.push_back(min);
    ret.push_back(max);
    return ret;
}

#endif //SYSMEASURE_COMMON_H
