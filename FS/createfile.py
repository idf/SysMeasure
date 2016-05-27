import os
import sys

with open(sys.argv[1], 'wb') as fout:
    fout.write(os.urandom(int(sys.argv[2]) * 1024 * 1024))