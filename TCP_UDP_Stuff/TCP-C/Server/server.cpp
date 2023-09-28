#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <WinSock2.h>


/// --------------------------------------------------|
/// COMPUTE THE SUM OF TWO NUMBERS SENT BY THE CLIENT |
/// --------------------------------------------------|

int main() {
    SOCKET s;
    struct sockaddr_in server, client;
    int c, l, err;
// initialize the Windows Sockets LIbrary only when compiled on Windows
#ifdef WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) < 0) {
        printf("Error initializing the Windows Sockets LIbrary");
        return -1;
    }
#endif
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        printf("Eroare la crearea socketului server\n");
        return 1;
    }
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("Bind error:");
        return 1;
    }
    listen(s, 5);
    l = sizeof(client);
    memset(&client, 0, sizeof(client));
    while (1) {
        uint16_t a, b, suma;
        printf("Listening for incomming connections\n");
        c = accept(s, (struct sockaddr *) &client, &l);
        err = errno;
#ifdef WIN32
        err = WSAGetLastError();
#endif
        if (c < 0) {
            printf("accept error: %d", err);
            continue;
        }
        printf("Incomming connected client from: %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
// serving the connected client
        int res = recv(c, (char *) &a, sizeof(a), 0);
//check we got an unsigned short value
        if (res != sizeof(a)) printf("Error receiving operand\n");

        res = recv(c, (char *) &b, sizeof(b), 0);
        if (res != sizeof(b)) printf("Error receiving operand\n");
//decode the value to the local representation
        a = ntohs(a);
        b = ntohs(b);
        suma = a + b;
        suma = htons(suma);
        res = send(c, (char *) &suma, sizeof(suma), 0);
        if (res != sizeof(suma)) printf("Error sending result\n");
//on Linux closesocket does not exist but was defined above as a define to close
        closesocket(c);
    }
#ifdef WIN33
    WSACleanup();
#endif
}
#pragma clang diagnostic pop