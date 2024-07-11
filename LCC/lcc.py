# FC - LCC simulator Code
import socket
import time 
import struct 
import threading 
import sys

def main():
    soc = socket.socket()
    soc.connect(("1.1.1.2" , 3003)) # FC-connect-EC port No. : 3003
    # soc.connect(("127.0.0.1" , 3002)) # LCC-connect-FC port No. : 3002  
    
    for i in sys.argv[2:]:
        # com = struct.pack ("=BBIBBBB ", 9, 2, 1000, 49, 0, 57, int(i)) # LCC
        com = struct.pack ("=BBIBBBB", 9, 2, 1000, 35, 0, 36 , int(i)) # FC
        print("sending cmd :",i)
        soc.send(com)
        time.sleep(float(sys.argv[1]))
        
    input()
    # soc.close()
main()