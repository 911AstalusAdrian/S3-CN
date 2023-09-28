#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <WinSock2.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

int digits(int number){
    int d = 0;
    while(number > 0){
        d = d+1;
        number = number / 10;
    }
    return d;
}


int main() {
    SOCKET s;
    struct sockaddr_in server, client;
    int c, l, err;

/// initialize the Windows Sockets LIbrary only when compiled on Windows
#ifdef WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) < 0) {
        printf("Error initializing the Windows Sockets LIbrary");
        return -1;}
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
        uint16_t nr,nr2  ,b[100], suma = 0;
        printf("\nListening for incomming connections\n");
        c = accept(s, (struct sockaddr *) &client, &l);
        err = errno;

        int number = rand() % 99999;

#ifdef WIN32
        err = WSAGetLastError();
#endif

        if (c < 0) {
            printf("accept error: %d", err);
            continue;
        }
        printf("Incomming connected client from: %s:%d", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        /// sending the number of digits to the client
        nr = htons(digits(number));
        send(c, (char*)&nr, sizeof(nr), 0);

//        int res = recv(c, (char*)&nr, sizeof(nr), 0);
//        //check we got an unsigned short value
//        if (res != sizeof(nr)) printf("Error receiving operand\n");
//        nr = ntohs(nr);
//        char a[50];
//        for(int i = 0; i <= nr; ++i){
//            res = recv(c, (char*)&a[i], sizeof(a[i]), 0);
//            if (res != sizeof(a[i])) printf("Error receiving operand\n");
//        }
//        printf("%s",a);
//        for(int i = 0; i <= nr; ++i){
//            printf("\n%c ",a[i]);
//            if(a[i] == ' ')
//            {
//                suma ++;
//            }
//        }
//        printf("\n%hu suma \n",suma);
//        suma = htons(suma);
//        res = send(c, (char*)&suma, sizeof(suma), 0);
//        if (res != sizeof(suma)) printf("Error sending result\n");

        closesocket(c);
    }
#ifdef WIN32
    WSACleanup();
#endif
}