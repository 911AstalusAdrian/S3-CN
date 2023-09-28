#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <WinSock2.h>
#include <sys/types.h>
#include <string.h>
#include <stdint.h>

/// SEND A STRING AND RECEIVE THE NUMBER OF SPACES IT HAS

int main() {
    int c;
    struct sockaddr_in server;
    uint16_t nr, suma;


    /// initialize the Windows Sockets LIbrary only when compiled on Windows
    #ifdef WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) < 0) {
        printf("Error initializing the Windows Sockets LIbrary");
        return -1;
    }
    #endif


    /// create the socket
    c = socket(AF_INET, SOCK_STREAM, 0);
    if (c < 0) {
        printf("Eroare la crearea socketului client\n");
        return 1;
    }

    /// connect the socket
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("Eroare la conectarea la server\n");
        return 1;
    }

    /// SEND A STRING AND RECEIVE THE NUMBER OF SPACES (LAB 1, PB2)
//    char buffer[256];
//    fgets(buffer, 256, stdin);
//    int characters = strlen(buffer);
//    int nr_server = htons(characters);
//    send(c, (char*)(&nr_server), sizeof(nr_server), 0);
//    for(int i = 0; i < characters ; i++){
//        //a[i] = htons(a[i]);
//        send(c, &buffer[i], sizeof(buffer[i]), 0);
//    }
//    recv(c, (char*)(&suma), sizeof(suma), 0);
//    suma = ntohs(suma);
//    printf("Suma este %hu\n", suma);


    /// SEND A STRING AND RECEIVE ITS REVERSE (LAB 1, PB3)
//    char buffer[256];
//    fgets(buffer, 256, stdin);
//    int characters = strlen(buffer);
//    int len = htons(characters);
//    printf("%d", characters);
//    send(c, (char*)(&len), sizeof(len), 0);
//    for(int i = 0; i < characters; i++)
//        send(c, &buffer[i], sizeof(buffer[i]), 0);
//
//    char final[256];
//    for(int i = 0; i < characters; i++)
//        recv(c, &final[i], sizeof(final[i]), 0);
//    printf("%s", final);


    /// SEND AN INT AND RECEIVE A LIST OF ITS DIVISORS (LAB 1, PB5)
//    int number, divisors[256];
//    scanf("%d", &number);
//    number = htons(number);
//    send(c, (char*)(&number), sizeof(number), 0);
//    int divs;
//    recv(c, (char*)(&divs), sizeof(divs), 0);
//    divs = ntohs(divs);
//    for(int i = 0; i < divs; i++)
//        recv(c, (char*)(&divisors[i]), sizeof(divisors[i]), 0);
//    for(int i = 0; i < divs; i++)
//        printf("%d ", divisors[i]);



    closesocket(c);
}