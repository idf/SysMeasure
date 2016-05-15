import socket
import sys

if __name__ == "__main__":
    HOST = sys.argv[1]          # localhost
    PORT = int(sys.argv[2])              # Arbitrary non-privileged port 50007

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((HOST, PORT))
    s.listen(1)
    print "server started"

    conn, addr = s.accept()
    print 'Connected by', addr
    while True:
        data = conn.recv(64)
        if not data: break
        conn.send(data)

    conn.close()
    print 'connection closed'

    s.close()
