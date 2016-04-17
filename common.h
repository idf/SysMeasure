//
// Created by MuyBien on 4/16/16.
//

#ifndef SYSMEASURE_COMMON_H
#define SYSMEASURE_COMMON_H


#include <cstdint>

static inline uint64_t rdtscStart(void){
    uint32_t cycles_high, cycles_low;
    asm volatile (
            "CPUID\n\t"/*serialize*/
            "RDTSC\n\t"/*read the clock*/
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            : "=r" (cycles_high), "=r" (cycles_low):: "%rax", "%rbx", "%rcx", "%rdx", "memory"
    );
    return (((uint64_t) cycles_high << 32)| cycles_low);
}

/*
Call the function to benchmark
*/

static inline uint64_t rdtscEnd(void){
    uint32_t cycles_high, cycles_low;
    asm volatile (
            "RDTSCP\n\t"/*read the clock*/
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            "CPUID\n\t"
            : "=r" (cycles_high), "=r"(cycles_low):: "%rax", "%rbx", "%rcx", "%rdx", "memory"
    );
    return (((uint64_t)cycles_high << 32) | cycles_low);
}




#endif //SYSMEASURE_COMMON_H
