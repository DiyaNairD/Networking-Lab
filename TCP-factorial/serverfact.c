#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int factorial(int a)
{
    int i, out = 1;
    for (i = 1; i <= a; i++)
    {
        out = out * i;
    }
    return out;
}

int main()
{
    char *ip = "127.0.0.1";
    int port = 5000;
    int p, b;
    char buffer[1024];
    
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    int n;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0)
    {
        perror("[-]Socket error");
        exit(1);
    }
    printf("[+]TCP server socket created.\n");

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);  // Use htons to convert port number to network byte order
    server_addr.sin_addr.s_addr = inet_addr(ip);

    n = bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (n < 0)
    {
        perror("[-]Bind error");
        exit(1);
    }
    printf("[+]Bind to the port number: %d\n", port);

    listen(server_sock, 5);
    printf("listening...\n");

    while (1)
    {
        addr_size = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);
        if (client_sock < 0)
        {
            perror("[-]Accept error");
            exit(1);
        }
        printf("[+]Client connected.\n");

        bzero(buffer, sizeof(buffer));
        recv(client_sock, buffer, sizeof(buffer), 0);
        printf("Client: %s\n", buffer);

        // Convert received string to integer
        p = atoi(buffer);
        b = factorial(p);

        // Convert integer result back to string and send it
        sprintf(buffer, "%d", b);
        send(client_sock, buffer, strlen(buffer), 0);

        close(client_sock);
        printf("[+]Client disconnected\n");
    }

    close(server_sock);
    return 0;
}

