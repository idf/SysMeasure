//
// Created by Danyang Zhang on 16/04/2016.
//

#include "CpuMeasurer.h"



void CpuMeasurer::readOverhead() {
    cout<< "Read Overhead:" << endl;
    run(&CpuMeasurer::_readOverhead, *this);
    cout<<endl;
}

void CpuMeasurer::loopOverhead() {
    cout<< "Loop Overhead:" << endl;
    run(&CpuMeasurer::_loopOverhead, *this);
    cout<<endl;
}

void CpuMeasurer::procedureCallOverhead() {
    cout<< "Procedure Call With 0 Argument:" << endl;
    run(&CpuMeasurer::_procedureCallOverhead0, *this);
    cout<<endl;

    cout<< "Procedure Call With 1 Argument:" << endl;
    run(&CpuMeasurer::_procedureCallOverhead1, *this);
    cout<<endl;

    cout<< "Procedure Call With 2 Argument:" << endl;
    run(&CpuMeasurer::_procedureCallOverhead2, *this);
    cout<<endl;

    cout<< "Procedure Call With 3 Argument:" << endl;
    run(&CpuMeasurer::_procedureCallOverhead3, *this);
    cout<<endl;

    cout<< "Procedure Call With 4 Argument:" << endl;
    run(&CpuMeasurer::_procedureCallOverhead4, *this);
    cout<<endl;

    cout<< "Procedure Call With 5 Argument:" << endl;
    run(&CpuMeasurer::_procedureCallOverhead5, *this);
    cout<<endl;

    cout<< "Procedure Call With 6 Argument:" << endl;
    run(&CpuMeasurer::_procedureCallOverhead6, *this);
    cout<<endl;

    cout<< "Procedure Call With 7 Argument:" << endl;
    run(&CpuMeasurer::_procedureCallOverhead7, *this);
    cout<<endl;
}

void CpuMeasurer::systemCallOverhead() {
    cout<< "Cached System Call:" << endl;
    run(&CpuMeasurer::_systemCallOverheadCached, *this);
    cout<<endl;

    cout<< "Uncached System Call:" << endl;
    run(&CpuMeasurer::_systemCallOverheadUncached, *this);
    cout<<endl;
}

void CpuMeasurer::taskCreationTime() {
    cout<< "Process Thread Creation:" << endl;
    run(&CpuMeasurer::_processThreadCreationTime, *this);
    cout<<endl;

    cout<< "Kernel Thread Creation:" << endl;
    run(&CpuMeasurer::_kernelThreadCreationTime, *this);
    cout<<endl;
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

double CpuMeasurer::_readOverhead() {
    unsigned long long start, end, diff;
    start = rdtscStart();
    end = rdtscEnd();
    diff = end - start;
    return diff;
}

double CpuMeasurer::_loopOverhead() {
    unsigned long long start, end, diff;
    start = rdtscStart();
    for(auto i=0; i<1000; i++) ;
    end = rdtscEnd();
    diff = end - start;
    return diff / 1000.0;
}


// measure procedure call overhead with different functions
double CpuMeasurer::_procedureCallOverhead0() {
    unsigned long long start, end, diff;
    start = rdtscStart();
    foo0();
    end = rdtscEnd();
    diff = end - start;
    return diff;
}

double CpuMeasurer::_procedureCallOverhead1() {
    unsigned long long start, end, diff;
    start = rdtscStart();
    foo1(1);
    end = rdtscEnd();
    diff = end - start;
    return diff;
}

double CpuMeasurer::_procedureCallOverhead2() {
    unsigned long long start, end, diff;
    start = rdtscStart();
    foo2(1,2);
    end = rdtscEnd();
    diff = end - start;
    return diff;
}

double CpuMeasurer::_procedureCallOverhead3() {
    unsigned long long start, end, diff;
    start = rdtscStart();
    foo3(1,2,3);
    end = rdtscEnd();
    diff = end - start;
    return diff;
}

double CpuMeasurer::_procedureCallOverhead4() {
    unsigned long long start, end, diff;
    start = rdtscStart();
    foo4(1,2,3,4);
    end = rdtscEnd();
    diff = end - start;
    return diff;
}

double CpuMeasurer::_procedureCallOverhead5() {
    unsigned long long start, end, diff;
    start = rdtscStart();
    foo5(1,2,3,4,5);
    end = rdtscEnd();
    diff = end - start;
    return diff;
}

double CpuMeasurer::_procedureCallOverhead6() {
    unsigned long long start, end, diff;
    start = rdtscStart();
    foo6(1,2,3,4,5,6);
    end = rdtscEnd();
    diff = end - start;
    return diff;
}

double CpuMeasurer::_procedureCallOverhead7() {
    unsigned long long start, end, diff;
    start = rdtscStart();
    foo7(1,2,3,4,5,6,7);
    end = rdtscEnd();
    diff = end - start;
    return diff;
}

double CpuMeasurer::_systemCallOverheadCached() {
    unsigned long long start, end, diff;
    start = rdtscStart();
    getpid();
    end = rdtscEnd();
    diff = end - start;
    return diff;
}

double CpuMeasurer::_systemCallOverheadUncached() {
    unsigned long long start, end, diff;
    start = rdtscStart();
    getppid();
    end = rdtscEnd();
    diff = end - start;
    return diff;
}

double CpuMeasurer::_processThreadCreationTime() {
    unsigned long long start, end, diff;
    start = rdtscStart();

    pid_t pid = fork();
    if(pid==0) exit(1);
    else{
        wait(NULL);
        end = rdtscEnd();
    }

    diff = end - start;
    return diff;
}

void* startThread(void*);

void* startThread(void* tid){
    pthread_exit(0);
};

double CpuMeasurer::_kernelThreadCreationTime() {
    unsigned long long start, end, diff;
    start = rdtscStart();

    pthread_t thread;
    pthread_create(&thread, NULL, &startThread, NULL);
    pthread_join(thread, NULL);
    end = rdtscEnd();

    diff = end - start;
    return diff;
}
























