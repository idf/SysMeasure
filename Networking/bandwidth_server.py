from _socket import SOL_SOCKET, SO_REUSEADDR
import os
import socket
import sys
import time

if __name__ == "__main__":
    HOST = sys.argv[1]
    PORT = int(sys.argv[2])
    FILE_SIZE = int(sys.argv[3])  # in MB

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)  # reuse address
    s.bind((HOST, PORT))
    s.listen(1)


    conn, addr = s.accept()
    print 'Connected by', addr
    while True:
        data = conn.recv(32)
        if data == 'client starts':
            content = os.urandom(int(FILE_SIZE) * 1024)
            conn.send('server starts')
            conn.sendall(content)

        elif data == 'client stops':
            break
        else:
            continue

    conn.close()
    s.close()
    print 'connection closed'


