//
// Created by Danyang Zhang on 16/04/2016.
//

#include "CpuMeasurer.h"

void CpuMeasurer::measurementOverhead() {
    run(&CpuMeasurer::_measurementOverhead, *this);
}

void CpuMeasurer::procedureCallOverhead() {

}

void CpuMeasurer::systemCallOverhead() {

}

void CpuMeasurer::taskCreationTime() {

}

void CpuMeasurer::contextSwitchTime() {

}

void CpuMeasurer::run(double (CpuMeasurer::*f)(), CpuMeasurer& cm) {
    vector<double> ret;
    for (auto i = 0; i < EXPERIMENTS; i++) {
        unsigned long long clock_total = 0;

        for (auto i = 0; i < TIMES_PER_EXPERIMENT; i++) {
            double time = (cm.*f)();
            clock_total += time;
        }
        auto mean = (double) clock_total / TIMES_PER_EXPERIMENT;
        cout << mean << endl;
        ret.push_back(mean);
    }
    stats(ret);
}

double CpuMeasurer::_measurementOverhead() {
    unsigned long long start, end, diff;
    start = rdtscStart();
    end = rdtscEnd();
    diff = end - start;
    return diff;
}













