//
// Created by Danyang Zhang on 16/04/2016.
//

#include "CpuMeasurer.h"
#include "pthread.h"

void CpuMeasurer::readOverhead() {
    cout << "Read Overhead:" << endl;
    run(&CpuMeasurer::_readOverhead);
    cout << endl;
}

void CpuMeasurer::loopOverhead() {
    cout << "Loop Overhead:" << endl;
    run(&CpuMeasurer::_loopOverhead);
    cout << endl;
}

void CpuMeasurer::procedureCallOverhead() {
    cout << "Procedure Call With 0 Argument:" << endl;
    run(&CpuMeasurer::_procedureCallOverhead0);
    cout << endl;

    cout << "Procedure Call With 1 Argument:" << endl;
    run(&CpuMeasurer::_procedureCallOverhead1);
    cout << endl;

    cout << "Procedure Call With 2 Argument:" << endl;
    run(&CpuMeasurer::_procedureCallOverhead2);
    cout << endl;

    cout << "Procedure Call With 3 Argument:" << endl;
    run(&CpuMeasurer::_procedureCallOverhead3);
    cout << endl;

    cout << "Procedure Call With 4 Argument:" << endl;
    run(&CpuMeasurer::_procedureCallOverhead4);
    cout << endl;

    cout << "Procedure Call With 5 Argument:" << endl;
    run(&CpuMeasurer::_procedureCallOverhead5);
    cout << endl;

    cout << "Procedure Call With 6 Argument:" << endl;
    run(&CpuMeasurer::_procedureCallOverhead6);
    cout << endl;

    cout << "Procedure Call With 7 Argument:" << endl;
    run(&CpuMeasurer::_procedureCallOverhead7);
    cout << endl;
}

void CpuMeasurer::systemCallOverhead() {
    cout << "Cached System Call:" << endl;
    run(&CpuMeasurer::_systemCallOverheadCached);
    cout << endl;

    cout << "Uncached System Call:" << endl;
    run(&CpuMeasurer::_systemCallOverheadUncached);
    cout << endl;
}

void CpuMeasurer::taskCreationTime() {
    cout << "Process Thread Creation:" << endl;
    run(&CpuMeasurer::_processThreadCreationTime);
    cout << endl;

    cout << "Kernel Thread Creation:" << endl;
    run(&CpuMeasurer::_kernelThreadCreationTime);
    cout << endl;
}

void CpuMeasurer::contextSwitchTime() {
    cout << "Process Context Swtich: " << endl;
    runAndFilter(&CpuMeasurer::_processContextSwitchTime);
    cout << endl;

    cout << "Thread Context Switch" << endl;
    run(&CpuMeasurer::_threadContextSwitchTime);
    cout << endl;
}

void CpuMeasurer::run(double (CpuMeasurer::*f)()) {
    vector<double> ret;
    for (auto i = 0; i < EXPERIMENTS; i++) {
        unsigned long long clock_total = 0;

        for (auto i = 0; i < TIMES_PER_EXPERIMENT; i++) {
            double time = (this->*f)();  // attach the method to a instance
            clock_total += time;
        }
        auto mean = (double) clock_total / TIMES_PER_EXPERIMENT;
        cout << mean << endl;
        ret.push_back(mean);
    }
    stats(ret);
}

void CpuMeasurer::runAndFilter(double (CpuMeasurer::*f)()) {
    vector<double> ret;
    for (auto i = 0; i < EXPERIMENTS; i++) {
        unsigned long long clock_total = 0;
        auto count = 0;

        for (auto i = 0; i < TIMES_PER_EXPERIMENT; i++) {
            double time = (this->*f)();  // attach the method to an instance
            if (time > 0) {
                clock_total += time;
                count++;
            }
        }
        double mean;
        if (count > 0) mean = (double) clock_total / count;
        else mean = 0;
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

    int repeat = 1;
    start = rdtscStart();
    for (auto i = 0; i < repeat; i++);
    end = rdtscEnd();
    diff = end - start;

    return (double) (diff - 33) / repeat;
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
    foo2(1, 2);
    end = rdtscEnd();
    diff = end - start;
    return diff;
}

double CpuMeasurer::_procedureCallOverhead3() {
    unsigned long long start, end, diff;
    start = rdtscStart();
    foo3(1, 2, 3);
    end = rdtscEnd();
    diff = end - start;
    return diff;
}

double CpuMeasurer::_procedureCallOverhead4() {
    unsigned long long start, end, diff;
    start = rdtscStart();
    foo4(1, 2, 3, 4);
    end = rdtscEnd();
    diff = end - start;
    return diff;
}

double CpuMeasurer::_procedureCallOverhead5() {
    unsigned long long start, end, diff;
    start = rdtscStart();
    foo5(1, 2, 3, 4, 5);
    end = rdtscEnd();
    diff = end - start;
    return diff;
}

double CpuMeasurer::_procedureCallOverhead6() {
    unsigned long long start, end, diff;
    start = rdtscStart();
    foo6(1, 2, 3, 4, 5, 6);
    end = rdtscEnd();
    diff = end - start;
    return diff;
}

double CpuMeasurer::_procedureCallOverhead7() {
    unsigned long long start, end, diff;
    start = rdtscStart();
    foo7(1, 2, 3, 4, 5, 6, 7);
    end = rdtscEnd();
    diff = end - start;
    return diff;
}

double CpuMeasurer::_systemCallOverheadCached() {
    unsigned long long start, end, diff;
    start = rdtscStart();
    getpid();  // TODO, change to another sys call to avoid repetition
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
    end = rdtscEnd();

    if (pid == 0) exit(1);
    else {
        wait(NULL);
    }

    diff = end - start;
    return diff;

}

void *startThread(void *);

void *startThread(void *tid) {
    pthread_exit(0);
};

double CpuMeasurer::_kernelThreadCreationTime() {
    unsigned long long start, end, diff;
    pthread_t thread;

    start = rdtscStart();
    pthread_create(&thread, NULL, &startThread, NULL);
    end = rdtscEnd();

    pthread_join(thread, NULL);

    diff = end - start;
    return diff;
}

// runAndFilter version
double CpuMeasurer::_processContextSwitchTime() {
    int fd[2];
    /*
     * pipefd[0] refers to the read end of the pipe.
     * pipefd[1] refers to the write end of the pipe.
     */
    pipe(fd);

    long long start, end, diff;
    pid_t cpid = fork();
    if (cpid > 0) { // parent
        start = rdtscStart();
        wait(NULL);  // wait for child
        read(fd[0], (void *) &end, sizeof(uint64_t));
    }
    else if (cpid == 0) { // child
        end = rdtscEnd();
        write(fd[1], (void *) &end, sizeof(uint64_t));
        exit(1);
    }
    else {
        cout << "fork() failed!" << endl;
    }
    close(fd[0]);
    close(fd[1]);

    diff = end - start;
    if (diff > 0) {
        return diff;
    }
    else {
        return -1;
    }
}

pthread_mutex_t LOCK;
void *_target(void *ret) {
    pthread_mutex_lock(&LOCK);
    uint64_t end = rdtscEnd();
    pthread_mutex_unlock(&LOCK);

    *((uint64_t *) ret) = end;
    pthread_exit(NULL);
}

double CpuMeasurer::_threadContextSwitchTime() {
    long long start, end, diff;

    pthread_mutex_init(&LOCK, NULL);

    pthread_mutex_lock(&LOCK);
    pthread_t thread;
    pthread_create(&thread, NULL, _target, &end);
    start = rdtscStart();  // include lock time
    pthread_mutex_unlock(&LOCK);

    pthread_join(thread, NULL);

    if (start > end) cout << "ERROR" << endl;
    diff = abs(start - end);
    return diff;
}