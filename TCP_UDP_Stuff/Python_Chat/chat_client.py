import socket, threading, sys, time, datetime, select

if __name__ == "__main__":

    clnt_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
    clnt_sock.connect(("192.168.1.194", 7000)) # Modify with your own address

    main_fds_list = [sys.stdin, clnt_sock]
    
    while True:

        curr_fds_list, _, _ = select.select(main_fds_list, [], [])

        for curr_fd in curr_fds_list:

            if curr_fd == sys.stdin:

                msg = input()
                clnt_sock.sendall(bytes(msg, 'ascii'))

            else:

                msg = curr_fd.recv(256)
                msg = msg.decode('ascii')
                print(msg)
