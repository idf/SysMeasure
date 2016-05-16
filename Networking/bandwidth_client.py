import socket
import time
import sys


if __name__ == "__main__":
    HOST = sys.argv[1]
    PORT = int(sys.argv[2])
    FILE_SIZE = int(sys.argv[3])  # in MB

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))

    for _ in xrange(100):
        s.send('client start')
        s.recv(1024)

        print 'start data'
        total_time = 0
        data = ''
        fileSize = int(FILE_SIZE) * 1024
        while sys.getsizeof(data) < fileSize:
            start = time.time()
            data += s.recv(fileSize)  # client receives server's data
            end = time.time()
            total_time += end - start

        ret = total_time * 1000  # in ms
        datasz = sys.getsizeof(data)
        print datasz, "byte"  # in byte
        average = float(datasz) / ret / 1000      # bandwidth
        print '%.2f %.2f MB/s' % (ret, average)

    s.close()
