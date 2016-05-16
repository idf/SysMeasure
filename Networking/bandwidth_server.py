import os
import socket
import sys

if __name__ == "__main__":
    HOST = sys.argv[1]
    PORT = int(sys.argv[2])
    FILE_SIZE = int(sys.argv[3])  # in MB

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((HOST, PORT))
    s.listen(1)

    while True:
        conn, addr = s.accept()
        print 'Connected by', addr

        while True:
            data = conn.recv(1024)
            if not data: continue

            content = os.urandom(int(FILE_SIZE) * 1024 - 37)
            # print 'server starts to send %d byte' % sys.getsizeof(content)
            conn.send(data)
            conn.sendall(content)

        conn.close()
        print 'connect closed'

    s.close()