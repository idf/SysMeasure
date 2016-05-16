import socket
import time
import sys
RUNS = 100

if __name__ == "__main__":
    HOST = sys.argv[1]
    PORT = int(sys.argv[2])
    FILE_SIZE = int(sys.argv[3])  # in MB

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))

    speed_max = 0
    for _ in xrange(RUNS):
        s.send('client start')
        total_time = 0
        data = ''
        fileSize = int(FILE_SIZE) * 1024
        while sys.getsizeof(data) < fileSize:
            start = time.time()
            data += s.recv(1024)  # client receives server's data
            end = time.time()
            total_time += end - start

        ret = total_time * 1000  # in ms
        datasz = sys.getsizeof(data)
        speed = float(datasz) / ret / 1000      # bandwidth
        print "%.2f MB/s" % speed
        speed_max = max(speed_max, speed)


    print fileSize, "byte"  # in byte
    print 'peek bandwidth %.2f MB/s' % speed_max
    s.close()
