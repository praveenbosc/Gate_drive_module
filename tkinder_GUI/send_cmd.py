import socket
import time
import struct
import threading
import sys

def main():
    s=socket.socket()
    s.connect(("127.0.0.1", 3003))

    cmd = struct.pack("=BBIBBBB", 9, 2, 1000, 35, int(sys.argv[1]), 36, int(sys.argv[2]))
    s.send(cmd)
    
    s.close()


main()
