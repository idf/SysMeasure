import socket
import sys
import time

if __name__ == "__main__":
    HOST = sys.argv[1]      # The host
    PORT = sys.argv[2]      # The same port as used by the server

    for i in xrange(0100):
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        start = time.time()
        s.connect((HOST, PORT))
        end = time.time()
        print (end - start) * 1000
        s.close()
