#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
int main() {

    int sock;
    struct sockaddr_in server;
    uint16_t suma;
    sock= socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {

            printf("Eroare la crearea socketului client\n");

            return 1;

    }



    memset(&server, 0, sizeof(server));

    server.sin_port = htons(1234);

    server.sin_family = AF_INET;

    server.sin_addr.s_addr = inet_addr("127.0.0.1");



    if (connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {

            printf("Eroare la conectarea la server\n");

            return 1;

    }
    int a[4];
    uint16_t count=5;
    uint16_t b;
    count=htons(count);
    send(sock, &count, sizeof(count), 0);
    printf("Give 5 numbers\n");
    for(int i=0;i<=4;i++){
        scanf("%i",&a[i]);
        b=htons(a[i]);
        send(sock,&b,sizeof(b),0);
    }
    recv(sock, &suma, sizeof(suma), 0);

    suma = ntohs(suma);

    printf("Suma este %hu\n", suma);

    close(sock);

}