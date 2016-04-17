//
// Created by Danyang Zhang on 16/04/2016.
//
#include <cmath>
#include <numeric>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>

#include "../lib/rdtscp.h"

using namespace std;

vector<double> stats(vector<double> v) {
  double sum = std::accumulate(v.begin(), v.end(), 0.0);
  double mean = sum / v.size();

  double sq_sum = std::inner_product(v.begin(), v.end(), v.begin(), 0.0);
  double stdev = std::sqrt(sq_sum / v.size() - mean * mean);
  cout << "mean: " << mean << endl;
  cout << "stdev: " << stdev << endl;
  vector<double> ret;
  ret.push_back(mean);
  ret.push_back(stdev);
  return ret;
}

int main() {

    cout << "Measurement Overhead" << endl;

    unsigned long clock_total = 0;

    int i;
    vector<double> ret;
    for (i = 0; i < 10; i++) {
        unsigned long long start, end;
        start = rdtsc();
        end = rdtsc();
        unsigned long long diff = end - start;
        clock_total = clock_total + diff;
        ret.push_back(diff);
        printf("%llu\n", diff);
    }
    stats(ret);
}
