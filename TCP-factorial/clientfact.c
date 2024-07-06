#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    char *ip = "127.0.0.1";
    int port = 5000;
    int client_sock;
    struct sockaddr_in server_addr;
    char buffer[1024];
    int number;

    client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock < 0) {
        perror("Socket creation error");
        exit(1);
    }
    printf("Client socket created.\n");

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    if (connect(client_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(1);
    }
    printf("Connected to the server.\n");

    // Input the number whose factorial you want to calculate
    printf("Enter a number to calculate its factorial: ");
    scanf("%d", &number);

    // Convert integer to string and send to server
    sprintf(buffer, "%d", number);
    send(client_sock, buffer, strlen(buffer), 0);
    printf("Number sent to server: %s\n", buffer);

    // Receive the result from server
    bzero(buffer, sizeof(buffer));
    recv(client_sock, buffer, sizeof(buffer), 0);
    printf("Factorial received from server: %s\n", buffer);

    close(client_sock);
    return 0;
}

