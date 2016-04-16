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

using namespace std;

int main() {

    cout << "Measurement Overhead" << endl;

    unsigned long clock_total = 0;

    int i;
    for (i = 0; i < 10; i++) {
        unsigned long long start, end;
        start = rdtsc();
        end = rdtsc();
        unsigned long long diff = end - start;
        clock_total = clock_total + diff;
        printf("%llu\n", diff);
    }

}