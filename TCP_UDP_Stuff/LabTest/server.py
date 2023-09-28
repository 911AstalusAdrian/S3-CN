import socket
import threading
import random
import struct
import sys
import time
from random import randint

if __name__=='__main__':
    try:
        rs=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        rs.bind( ('192.168.1.6',1234) )
        rs.listen(5)
    except socket.error as msg:
        print(msg.strerror)
        exit(-1)

    while True:
        number = randint(0, 999999)
        digits = len(str(number))
        try:
            rs.sendall(struct.pack('!I', digits))
            answer = rs.recv(1)
        except socket.error as msg:
            print('Error: ',msg.strerror)
            s.close()
            exit(-2)
