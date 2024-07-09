// server.c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<time.h>

#define BUFFER_SIZE 1024

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int port = atoi(argv[1]);
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[BUFFER_SIZE];
    int n;
    time_t current_time;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("[-] Socket error");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("[-] Binding error");
        close(sockfd);
        exit(1);
    }

    printf("[+] Server listening on port %d\n", port);

    while (1) {
        addr_size = sizeof(client_addr);
        n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_size);
        if (n < 0) {
            perror("[-] Error receiving data");
            exit(1);
        }
        buffer[n] = '\0'; // Ensure buffer is null-terminated

        printf("[+] Data received from client: %s\n", buffer);

        // Get current time
        current_time = time(NULL);
        snprintf(buffer, BUFFER_SIZE, "%s", ctime(&current_time));

        // Send current time back to client
        n = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr, addr_size);
        if (n < 0) {
            perror("[-] Error sending data");
            exit(1);
        }
        printf("[+] Time sent to client: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}

