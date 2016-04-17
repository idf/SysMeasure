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
#include <unistd.h>

#include "../lib/rdtscp.h"
#include "../common.h"

class CpuMeasurer {
public:
    const int EXPERIMENTS = 10;
    const int TIMES_PER_EXPERIMENT = 100;

    void run(double (CpuMeasurer::*f)(), CpuMeasurer& cm);

    void readOverhead();
    double _readOverhead();

    void loopOverhead();
    double _loopOverhead();

    void procedureCallOverhead();
    double _procedureCallOverhead0();
    double _procedureCallOverhead1();
    double _procedureCallOverhead2();
    double _procedureCallOverhead3();
    double _procedureCallOverhead4();
    double _procedureCallOverhead5();
    double _procedureCallOverhead6();
    double _procedureCallOverhead7();

    void systemCallOverhead();
    double _systemCallOverheadCached();
    double _systemCallOverheadUncached();

    void taskCreationTime();
    double _processThreadCreationTime();
    double _kernelThreadCreationTime();

    void contextSwitchTime();

    // output format:
    // task description
    // mean #1
    // mean #2
    // ...
    // mean of means
    // stdev of means

    void foo0(){};
    void foo1(int){};
    void foo2(int, int ){};
    void foo3(int, int, int){};
    void foo4(int, int, int, int){};
    void foo5(int, int, int, int, int){};
    void foo6(int, int, int, int, int, int){};
    void foo7(int, int, int, int, int, int, int){};


};


#endif //SYSMEASURE_CPUMEASURER_H
