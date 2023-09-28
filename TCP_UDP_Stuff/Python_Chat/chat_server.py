import socket, threading, sys, time, datetime, select

if __name__ == "__main__":

    client_count = 0
    sock_dict = {}

    srv_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
    srv_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    srv_sock.bind(("192.168.1.194", 7000)) # Modify with your own address
    
    main_fds_list = [srv_sock]

    srv_sock.listen(10)

    while True:

        curr_fds_list, _, _ = select.select(main_fds_list, [], [])

        for curr_fd in curr_fds_list:

            if curr_fd == srv_sock:

                new_fd, new_addr = srv_sock.accept()

                main_fds_list.append(new_fd)

                sock_dict[new_fd] = new_addr

                print("New client connected from " + str(new_addr[0]) + ":" + str(new_addr[1]) + " ; socket #" + str(new_fd.fileno()))

                client_count += 1
                connect_msg = "[PRIVATE] You successfully connected to the server.\n          You are client with ID #" + str(new_fd.fileno()) + ". There are currently " + str(client_count) + " connected."

                new_fd.sendall(bytes(connect_msg, 'ascii'))

            else:

                public_msg = curr_fd.recv(256) 

                public_msg = public_msg.decode('ascii')

                if len(public_msg) <= 0:

                    if len(public_msg) == 0:
                        
                        print("Client #" + str(curr_fd.fileno()) + " has forcibly hung up.")
                    
                    else:

                        print("Error on receiving message.")

                    for index in range(len(main_fds_list)):

                        if main_fds_list[index] == curr_fd:

                            del main_fds_list[index]
                            break
                    
                    del sock_dict[curr_fd]

                    socket.close(curr_fd.fileno())
                    client_count -= 1

                else:

                    print("Public message sent by " + str(sock_dict[curr_fd][0]) + ":" + str(sock_dict[curr_fd][1]) + " ; socket #" + str(curr_fd.fileno()) + " : " + public_msg)

                    public_msg = "[PUBLIC] " + public_msg

                    for fd in main_fds_list:

                        if fd != srv_sock and fd != curr_fd:

                            fd.sendall(bytes(public_msg, 'ascii'))
                    
                
                

                