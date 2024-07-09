// client.c
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
    if (argc != 3) {
        printf("Usage: %s <ip> <port>\n", argv[0]);
        exit(1);
    }

    char *ip = argv[1];
    int port = atoi(argv[2]);
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t addr_size;
    char buffer[BUFFER_SIZE];
    int n;
    time_t start_time, end_time;
    double rtt_ms;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("[-] Socket error");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    strcpy(buffer, "What is the current time?");
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("[+] Request sent: %s\n", buffer);

    addr_size = sizeof(server_addr);
    n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, &addr_size);
    if (n < 0) {
        perror("[-] Error receiving data");
        close(sockfd);
        exit(1);
    }
    buffer[n] = '\0'; 

    end_time = time(NULL);
    rtt_ms = difftime(end_time, start_time) * 1000.0;

    printf("[+] Time received from server: %s\n", buffer);
    printf("    Round-trip time: %.2f milliseconds\n", rtt_ms);

    close(sockfd);
    return 0;
}

