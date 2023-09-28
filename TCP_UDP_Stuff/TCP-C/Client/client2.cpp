//#pragma comment(lib, "ws2_32.lib")
//#define _WINSOCK_DEPRECATED_NO_WARNINGS
//#include <iostream>
//#include <stdio.h>
//#include <WinSock2.h>
//#include <sys/types.h>
//#include <string>
//
///// SEND A STRING AND RECEIVE THE NUMBER OF SPACES IT HAS
//
//int main() {
//    int c;
//    struct sockaddr_in server;
//    uint16_t nr, suma;
//
//
//    /// initialize the Windows Sockets LIbrary only when compiled on Windows
//    #ifdef WIN32
//    WSADATA wsaData;
//    if (WSAStartup(MAKEWORD(2, 2), &wsaData) < 0) {
//        printf("Error initializing the Windows Sockets LIbrary");
//        return -1;
//    }
//    #endif
//
//
//    /// create the socket
//    c = socket(AF_INET, SOCK_STREAM, 0);
//    if (c < 0) {
//        printf("Eroare la crearea socketului client\n");
//        return 1;
//    }
//
//    /// connect the socket
//    memset(&server, 0, sizeof(server));
//    server.sin_port = htons(1234);
//    server.sin_family = AF_INET;
//    server.sin_addr.s_addr = inet_addr("127.0.0.1");
//    if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
//        printf("Eroare la conectarea la server\n");
//        return 1;
//    }
//
//    /// SEND A STRING AND RECEIVE THE NUMBER OF SPACES (LAB 1, PB2)
////    char buffer[256];
////    fgets(buffer, 256, stdin);
////    int characters = strlen(buffer);
////    int nr_server = htons(characters);
////    send(c, reinterpret_cast<const char *>(&nr_server), sizeof(nr_server), 0);
////    for(int i = 0; i < characters ; i++){
////        //a[i] = htons(a[i]);
////        send(c, &buffer[i], sizeof(buffer[i]), 0);
////    }
////    recv(c, reinterpret_cast<char *>(&suma), sizeof(suma), 0);
////    suma = ntohs(suma);
////    printf("Suma este %hu\n", suma);
//
//
//    /// SEND A STRING AND RECEIVE ITS REVERSE (LAB 1, PB3)
//    char buffer[256];
//    fgets(buffer, 256, stdin);
//    int characters = strlen(buffer);
//    int len = htons(characters);
//    printf("%d", characters);
//    send(c, reinterpret_cast<const char *>(&len), sizeof(len), 0);
//    for(int i = 0; i < characters; i++)
//        send(c, &buffer[i], sizeof(buffer[i]), 0);
//
//    closesocket(c);
//
//}