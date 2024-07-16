#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <arpa/inet.h>

typedef struct
{
    uint8_t start_of_frame;
    uint8_t packet_identifier;
    uint8_t data1;
    uint8_t data2;
    uint8_t checksum;
} Send_packet __attribute__((packed));

typedef struct
{
    uint8_t start_of_frame;
    uint8_t data[14];
    uint8_t checksum;
} Receive_packet __attribute__((packed));

Receive_packet rcv_s;
Send_packet buffer;

#define NUM_THREADS 2
void *server_thread_2(int *client_fd);
void *server_thread_4(int *client_fd);

void *server_thread_0(void *arg)
{
    int thread_id = *((int *)arg);
    // Create socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, 0, 0);
    if(server_fd<0)
    {
        perror("Error opening socket");
        exit(1);
    }

    // Bind to address
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(thread_id);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == -1)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 1) == -1)
    {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf(" HELLO Thread %d listening on port %d\n", thread_id, thread_id);

    // Accept incoming connection
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_fd <= 0)
    {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    pthread_t threads_1,threads_2;
    if (pthread_create(&threads_1, NULL, server_thread_2, &client_fd) != 0)
    {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&threads_2, NULL, server_thread_4, &client_fd) != 0)
    {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    pthread_join(threads_1, NULL);
    pthread_join(threads_2, NULL);

    close(client_fd);
    close(server_fd);
    return NULL;
}

void *server_thread_2(int *client_fd)
{
    int bytes_received = 0;
    while (1)
    {
        bytes_received = recv(*client_fd, &buffer, sizeof(buffer), 0);
        if (bytes_received <= 0)
        {
            printf("exit\t");
            printf("errno:%d\n", errno);
        }
        else
        {
            printf("buffer.start_of_frame : %d ,buffer.packet_identifier : %d ,buffer.data1 : %d ,buffer.data2 : %d ,buffer.checksum : %d \n", buffer.start_of_frame, buffer.packet_identifier, buffer.data1, buffer.data2, buffer.checksum);
        }
    }
}
void *server_thread_4(int *client_fd)
{
    while (1)
    {
        rcv_s.start_of_frame = 99;
        for (int i = 0; i <= 14; i++)
        {
            rcv_s.data[i] = i + 20;
        }

        rcv_s.checksum ^= rcv_s.start_of_frame;
        for (int i = 0; i < 14; i++)
        {
            rcv_s.checksum ^= rcv_s.data[i];
        }

        if (send(*client_fd, &rcv_s, sizeof(rcv_s), 0) == -1)
        {
            perror("send_failed");
            exit(1);
        }
        printf("Sending\t      ");
        usleep(100000);
    }
}

void *server_thread_1(void *arg)
{
    int thread_id = *((int *)arg);
    // Create socket
    int server_fd_1 = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd_1 == -1)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Bind to address
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(thread_id);

    if (bind(server_fd_1, (struct sockaddr *)&address, sizeof(address)) == -1)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd_1, 1) == -1)
    {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Thread %d listening on port %d\n", thread_id, thread_id);

    // Accept incoming connection
    struct sockaddr_in client_addr_1;
    socklen_t client_addr_len_1 = sizeof(client_addr_1);
    int client_fd_1 = accept(server_fd_1, (struct sockaddr *)&client_addr_1, &client_addr_len_1);
    if (client_fd_1 <= 0)
    {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }
    Receive_packet rcv_p;
    while (1)
    {
        rcv_p.start_of_frame = 34;
        for (int i = 1; i <= 14; i++)
        {
            rcv_p.data[i] = i;
        }

        rcv_p.checksum ^= rcv_p.start_of_frame;
        for (int i = 0; i < 14; i++)
        {
            rcv_p.checksum ^= rcv_p.data[i];
        }

        if (send(client_fd_1, &rcv_p, sizeof(rcv_p), 0) == -1)
        {
            perror("send_failed");
            exit(1);
        }
        printf("Sending_1\t     ");
        usleep(100000);
    }

    close(client_fd_1);
    close(server_fd_1);
    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS] = {8003, 8004};

    if (pthread_create(&threads[0], NULL, server_thread_0, &thread_ids[0]) != 0)
    {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&threads[1], NULL, server_thread_1, &thread_ids[1]) != 0)
    {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    return 0;
}
