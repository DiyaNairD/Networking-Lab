// time_client.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        printf("Usage : %s <ip> <port>\n", argv[0]);
        exit(0);
    }
    
    char *ip = argv[1];
    int port = atoi(argv[2]);
    
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024];
    socklen_t addr_size;
    int n;
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0)
    {
        perror("[-] Socket error");
        exit(1);
    }
    
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip); 
    
    strcpy(buffer, "time");
    n = sendto(sockfd, buffer, strlen(buffer) + 1, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(n < 0)
    {
        perror("[-] Error sending data");
        exit(1);
    }
    printf("[+] Request sent: %s\n", buffer);
    
    bzero(buffer, 1024);
    addr_size = sizeof(server_addr);
    n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&server_addr, &addr_size);
    if(n < 0)
    {
        perror("[-] Error receiving data");
        exit(1);
    }
    printf("[+] Time received: %s\n", buffer);
    
    close(sockfd);
    
    return 0;
}
