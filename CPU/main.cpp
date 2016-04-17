//
// Created by Danyang Zhang on 16/04/2016.
//

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>

#include "../lib/rdtscp.h"
#include "../common.h"

using namespace std;

int main() {

    cout << "Measurement Overhead" << endl;

    unsigned long clock_total = 0;
    unsigned long long start, end;
    unsigned long long diff;

    int run_times = 10000;

    for (auto i = 0; i < run_times; i++) {
        start = rdtscStart();
        end = rdtscEnd();
        unsigned long long diff = end - start;
        clock_total = clock_total + diff;
//        printf("%llu\n", diff);
    }
    printf("Avg Read Overhead: %f\n", clock_total / (float)run_times);


    cout << "Loop Overhead" << endl;

    start = rdtscStart();
    for (auto i = 0; i < run_times; i++) {
    }
    end = rdtscEnd();
    diff = end - start;

    printf("Avg Loop Overhead: %f\n", diff / (float) run_times);

}