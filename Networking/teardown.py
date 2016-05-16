import socket
import sys
import time

if __name__ == "__main__":
    HOST = sys.argv[1]      # The host
    PORT = int(sys.argv[2])      # The same port as used by the server

    for i in xrange(100):
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect((HOST, PORT))
        start = time.time()
        s.close()
        # s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        end = time.time()
        print (end - start) * 1000
