//#pragma comment(lib, "ws2_32.lib")
//#define _WINSOCK_DEPRECATED_NO_WARNINGS
//#include <iostream>
//#include <stdio.h>
//#include <WinSock2.h>
//#include <sys/types.h>
//#include <string.h>
//

///// -----------------------------------|
///// CLIENT SENDS A STRING TO THE SERVER|
///// -----------------------------------|
//
//int main() {
//    WORD wVersionRequested;
//    WSADATA wsaData;
//    int err;
//
///* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
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
//    char buffer[1024];
//    scanf("%s", buffer);
//    int len = sizeof(struct sockaddr_in);
//
//
//
//    int n = sendto(sock, buffer, strlen(buffer)+1, 0, reinterpret_cast<const sockaddr *>(&server), len);
//
//    if (n <0 ) {
//        perror("error on sending data");
//        exit(-2);
//    }
//
//    int r = recvfrom(sock, buffer, 1024, 0, reinterpret_cast<sockaddr *>(&from), &len);
//    if (r <0 ) {
//        err = WSAGetLastError();
//        printf("codul de eroare e %d", err);
//        exit(-3);
//    }
//
//    printf("%s\n", buffer);
//
//    closesocket(sock);
//
//    return 0;
//
//}
