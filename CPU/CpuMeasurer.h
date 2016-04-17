//
// Created by Danyang Zhang on 16/04/2016.
//

#ifndef SYSMEASURE_CPUMEASURER_H
#define SYSMEASURE_CPUMEASURER_H

//
#include <iostream>
#include <fstream>
#include <set>
#include <string>

#include "../lib/rdtscp.h"
#include "../common.h"

class CpuMeasurer {
public:
    const int EXPERIMENTS = 10;
    const int TIMES_PER_EXPERIMENT = 100;

    void run(double (CpuMeasurer::*f)(), CpuMeasurer& cm);
    double _measurementOverhead();

    void measurementOverhead();
    void procedureCallOverhead();
    void systemCallOverhead();
    void taskCreationTime();
    void contextSwitchTime();

    // output format:
    // task description
    // mean #1
    // mean #2
    // ...
    // mean of means
    // stdev of means


};


#endif //SYSMEASURE_CPUMEASURER_H
