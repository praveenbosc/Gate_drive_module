#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>
#include <sys/time.h> // For gettimeofday()
#include <errno.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void getCurrentTimestamp(char *timestamp) {
    struct timespec ts;
    struct tm tm_info;

    if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
        perror("clock_gettime");
        exit(EXIT_FAILURE);
    }

    if (localtime_r(&ts.tv_sec, &tm_info) == NULL) {
        perror("localtime_r");
        exit(EXIT_FAILURE);
    }

    snprintf(timestamp, 40, "%04d-%02d-%02d %02d:%02d:%02d.%09ld",
             tm_info.tm_year + 1900, tm_info.tm_mon + 1, tm_info.tm_mday,
             tm_info.tm_hour, tm_info.tm_min, tm_info.tm_sec,
             ts.tv_nsec);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Setting up the address structure
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the network address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    // Accept an incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Read the message from the client
    int valread = read(new_socket, buffer, BUFFER_SIZE);
    if (valread < 0) {
        perror("read failed");
        close(new_socket);
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    char timestamp[40];
    getCurrentTimestamp(timestamp);

    printf("Message from client: %s\n", buffer);
    printf("Current timestamp: %s\n", timestamp);

    // Optionally, send a response back to the client
    // const char *response = "Hello from server";
    // send(new_socket, response, strlen(response), 0);
    // printf("Response sent\n");

    // Close the sockets
    close(new_socket);
    close(server_fd);

    return 0;
}

