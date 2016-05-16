import socket
import sys
import time

if __name__ == "__main__":
    HOST = sys.argv[1]      # The host
    PORT = int(sys.argv[2])      # The same port as used by the server

    with open('setup.txt', 'w') as f:
        for i in xrange(100):
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

            start = time.time()
            s.connect((HOST, PORT))
            end = time.time()

            s.close()
            f.write(str((end - start) * 1000) + '\n')
