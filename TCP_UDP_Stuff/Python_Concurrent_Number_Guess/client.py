import socket, struct, random,sys, time


if __name__ == '__main__':

    N = float(sys.argv[1])
    try:
        s = socket.create_connection( ('localhost',1234))
    except socket.error as msg:
        print("Error: ",msg.strerror)
        exit(-1)

    finished=False
    random.seed()

    data=s.recv(1024)
    print(data.decode('ascii'))
    data = s.recv(1024)
    print(data.decode('ascii'))
    string = data.decode('ascii')
    words = string.split()
    digits = int(words[3])

    mynum = [None] * digits
    guessed_digits = 0

    step_count=0
    while not finished:
        my_digit=random.randint(0,9)
        try:
            s.sendall( struct.pack('!I',my_digit) )
            answer=s.recv(4)
        except socket.error as msg:
            print('Error: ',msg.strerror)
            s.close()
            exit(-2)
        print('Sent ',my_digit,' Answer ',answer.decode('ascii'))
        if answer != b'N':
            ans = int(answer)
            if(mynum[ans] is None):
                guessed_digits += 1
                mynum[ans] = my_digit
            if guessed_digits == digits:
                # s.sendall(b'W')
                print('I am the winner')
                finished=True
        # s.sendall(b'C')
        time.sleep(N)

    s.close()
