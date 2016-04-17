//
// Created by Danyang Zhang on 16/04/2016.
//

#include "CpuMeasurer.h"

void CpuMeasurer::measurementOverhead() {
    unsigned long clock_total = 0;
    unsigned long long start, end;
    unsigned long long diff;
//    vector<double> ret;

    for (auto i = 0; i < TIMES_PER_EXPERIMENT; i++) {
        start = rdtscStart();
        end = rdtscEnd();
        diff = end - start;
//        ret.push_back(diff);

        clock_total = clock_total + diff;

        cout << diff << endl;
    }

    cout << (clock_total / (float)TIMES_PER_EXPERIMENT) << endl;
}

void CpuMeasurer::procedureCallOverhead() {

}

void CpuMeasurer::systemCallOverhead() {

}

void CpuMeasurer::taskCreationTime() {

}

void CpuMeasurer::contextSwitchTime() {

}









