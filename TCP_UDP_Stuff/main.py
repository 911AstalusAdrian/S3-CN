import datetime
import socket
import struct
import sys
import time
import threading
import re

port=1235

def time_query_worker(sock):
    while (True):
        time.sleep(3)
        message = "TIMEQUERY"
        print("Sending timequery")
        sock.sendto(message.encode(), (broadcast_addr, port))


def date_query_worker(sock):
    while (True):
        time.sleep(10)
        message = "DATEQUERY"
        print("Sending datequery")
        sock.sendto(message.encode(), (broadcast_addr, port))


def process_request(sock):

    while(True):

        message, address = sock.recvfrom(32)
        message = message.decode()
        if message == 'TIMEQUERY':
            my_time = 'TIME ' + time.strftime("%H:%M:%S")
            sock.sendto(my_time.encode(), address)
        elif message == 'DATEQUERY':
            my_date = 'DATE ' + str(datetime.date.today())
            sock.sendto(my_date.encode(), address)
        elif re.search("TIME [0-9][0-9]:[0-9][0-9]:[0-9][0-9]", message):
            print("Got time")
        elif re.search("DATE [0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9]", message):
            print("Got date")
        else:
            print("Malformed ", message)



client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
client_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
client_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
# client_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
client_socket.bind(("", port))

broadcast_addr = sys.argv[1]

tqthread = threading.Thread(target=time_query_worker, args=(client_socket,))
dqthread = threading.Thread(target=date_query_worker, args=(client_socket,))
prthread = threading.Thread(target=process_request, args=(client_socket,))
tqthread.start()
dqthread.start()
prthread.start()
prthread.join()
tqthread.join()
dqthread.join()

# time_reg = "TIME: [0-9][0-9] : [0-9][0-9] : [0-9][0-9]"
# date_reg = "DATE: [0-9][0-9] / [0-9][0-9] / [0-9][0-9]"
# string="TIME: 21d : 23 : 34"
# string_date="DATE: 22 / 13 / 99"
# reg=re.compile(time_reg)
# reg_date=re.compile(date_reg)
#
#
# print(reg.match(string))
# print(reg_date.match(string_date))