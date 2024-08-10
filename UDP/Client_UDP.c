#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 6969
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    const char *hello = "Hello from client";
    struct sockaddr_in servaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("1.1.1.111");
    // servaddr.sin_addr.s_addr = INADDR_ANY;
    int n, len;

    while(1)
    {    
        // // Send hello message to server
        sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));
        printf("Hello message sent.\n");
        printf("waiting for receive\n");
        // Receive server's response
        n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, 0, (struct sockaddr *)&servaddr, &len);
        buffer[n] = '\0';
        printf("Server : %s\n", buffer);
    }
    close(sockfd);
    return 0;
}


