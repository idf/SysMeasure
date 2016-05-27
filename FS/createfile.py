import os
import sys

with open(sys.argv[1], 'wb') as fout:
    fout.truncate(int(sys.argv[2]) * 1024 * 1024)