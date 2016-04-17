//
// Created by Danyang Zhang on 16/04/2016.
//
#include <iostream>
#include <fstream>
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

    vector<double> ret;
    auto run_times = 10000;

    for (auto i = 0; i < run_times; i++) {
        start = rdtscStart();
        end = rdtscEnd();
        unsigned long long diff = end - start;
        ret.push_back(diff);
        clock_total = clock_total + diff;
        // printf("%llu\n", diff);
    }
    stats(ret);



    cout << "Loop Overhead" << endl;

    start = rdtscStart();
    for (auto i = 0; i < run_times; i++) {
    }
    end = rdtscEnd();
    diff = end - start;

    printf("Avg Loop Overhead: %f\n", diff / (float) run_times);

}
