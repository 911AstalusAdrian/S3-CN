#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

typedef int SOCKET;
int main() {

    SOCKET s;
    struct sockaddr_in server,client;
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
    socklen_t client_len;
    int client_sock;
    while (1) {
        int suma=0;
        uint16_t count;
        uint16_t a;
        printf("Listening for incomming connections\n");
        client_sock = accept(s, (struct sockaddr *) &client, &client_len);
        printf("Socket :%d",client_sock);
        printf("\n");
        if (client_sock< 0) {
                printf("accept error: ");
                continue;
        }
        printf("Incomming connected client from: %s:%d", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
        printf("\n");
        int res = recv(client_sock, (char*)&count, sizeof(count), 0);
        if (res != sizeof(count)) printf("Error receiving operand\n");
        count = ntohs(count);
        for(int i=0;i<count;i++){
        res = recv(client_sock, (char*)&a, sizeof(a), 0);
        if (res != sizeof(a)) printf("Error receiving operand\n");
        a=ntohs(a);
        printf("Got :%d",a);
        printf("\n");
        suma = suma+a;
        }
        suma = htons(suma);
        res = send(client_sock, (char*)&suma, sizeof(suma), 0);
        if (res != sizeof(suma)) printf("Error sending result\n");
        close(client_sock);

        }
}