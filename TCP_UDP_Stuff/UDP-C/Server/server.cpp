//#pragma clang diagnostic push
//#pragma ide diagnostic ignored "EndlessLoop"
//#pragma comment(lib, "ws2_32.lib")
//#define _WINSOCK_DEPRECATED_NO_WARNINGS
//#include <iostream>
//#include <stdio.h>
//#include <WinSock2.h>
//
///// ----------------------------------|
///// RECIEVES STRING SENT BY THE CLIENT|
///// ----------------------------------|
//
//int main() {
//
//    WORD wVersionRequested;
//    WSADATA wsaData;
//    int err;
//
//    /* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
//    wVersionRequested = MAKEWORD(2, 2);
//
//    err = WSAStartup(wVersionRequested, &wsaData);
//    if (err != 0) {
//        /* Tell the user that we could not find a usable */
//        /* Winsock DLL.                                  */
//        printf("WSAStartup failed with error: %d\n", err);
//        return 1;
//    }
//
//    int sock = socket(AF_INET, SOCK_DGRAM, 0);
//    if (sock < 0) {
//        perror("error on creating socket!");
//        exit(-1);
//    }
//
//    struct sockaddr_in server, from;
//
//    memset(&server, 0, sizeof(server));
//
//    server.sin_family = AF_INET;
//    server.sin_port = htons(1234);
//    server.sin_addr.s_addr = inet_addr("127.0.0.1");
//
//    if (bind(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
//        int err = WSAGetLastError();
//        printf("codul de eroare e %d", err);
//        exit(-2);
//    }
//
//    char buffer[1024];
//    int from_len = sizeof(from);
//    int n = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)& from, &from_len);
//
//    if (n <0) {
//        err = WSAGetLastError();
//        printf("codul de eroare e %d", err);
//        exit(-3);
//    }
//
//    printf("%s\n", buffer);
//
//    int s = sendto(sock, "got your message\n", 18, 0, (struct sockaddr*)&from, from_len);
//    if (s <0) {
//        err = WSAGetLastError();
//        printf("codul de eroare e %d", err);
//        exit(-4);
//    }
//
//    return 0;
//
//}
//#pragma clang diagnostic pop