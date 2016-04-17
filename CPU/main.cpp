//
// Created by Danyang Zhang on 16/04/2016.
//
#include <cstdio>
#include <iostream>
#include "CpuMeasurer.h"

using namespace std;

int main() {
    const bool DEBUG = true;

    if (!DEBUG) {
        freopen("CPU/result/output.txt","w", stdout);
    }
    CpuMeasurer cpuMeasurer;

    cpuMeasurer.readOverhead();
    cpuMeasurer.loopOverhead();
    cpuMeasurer.procedureCallOverhead();
    cpuMeasurer.systemCallOverhead();
    cpuMeasurer.taskCreationTime();
    cpuMeasurer.contextSwitchTime();
}
