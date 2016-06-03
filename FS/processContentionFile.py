import numpy as np

__author__ = 'MuyBien'


prefix = "result_contention/"
# file = prefix + "result_sequential_contention.txt"
# file = prefix + "result_random_contention.txt"
# file = prefix + "result_sequential_contention_mixed.txt"
file = prefix + "result_random_contention_mixed.txt"

lines = open(file).readlines()

i = 0
while i < len(lines):
    i += 1
    data = []
    for j in xrange(20):
        data.append(float(lines[i+j]))
    print np.mean(data)
    # print np.std(data)
    i += 21

