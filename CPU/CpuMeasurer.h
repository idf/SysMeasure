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
    const int TIMES = 100;
    void measurementOverhead();
    void procedureCallOverhead();
    void systemCallOverhead();
    void taskCreationTime();
    void contextSwitchTime();



};


#endif //SYSMEASURE_CPUMEASURER_H
