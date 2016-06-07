import socket
import time
import sys


if __name__ == "__main__":

    HOST = sys.argv[1]
    PORT = int(sys.argv[2])

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))
    print "client started"
    with open(HOST + '.txt', 'w') as f:
        for k in xrange(100):
            total = 0
            for _ in xrange(100):

                start = time.time()
                s.send('0'*63)
                data = s.recv(64)
                end = time.time()

                total += end - start

            result = total * 1000 / 100.0  # in ms
            f.write(str(result) + '\n')

    s.close()
