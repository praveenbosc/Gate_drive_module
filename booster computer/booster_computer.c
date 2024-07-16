#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define NUM_ENGINES 7
#define BASE_PORT 8080

int engine_sockets[NUM_ENGINES];

void init_connections()
{
    struct sockaddr_in address;
    for (int i = 0; i < NUM_ENGINES; ++i)
    {
        int port = BASE_PORT + i;
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0)
        {
            perror("Socket creation error");
            exit(EXIT_FAILURE);
        }

        address.sin_family = AF_INET;
        address.sin_port = htons(port);

        if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0)
        {
            perror("Invalid address / Address not supported");
            exit(EXIT_FAILURE);
        }

        if (connect(sock, (struct sockaddr *)&address, sizeof(address)) < 0)
        {
            perror("Connection failed");
            close(sock);
            continue; // Try next engine
        }

        engine_sockets[i] = sock;
        printf("Connected to engine %d on port %d\n", i, port);
    }
}

void send_rpm_all(int rpm)
{
    char message[256];
    snprintf(message, sizeof(message), "ENGINE_ID 0 Common rpm %d", rpm);
    for (int i = 0; i < NUM_ENGINES; ++i)
    {
        if (engine_sockets[i] != 0)
        {
            send(engine_sockets[i], message, strlen(message), 0);
        }
    }
}

void send_rpm_to_engine(int engine_id, int rpm)
{
    if (engine_id < 0 || engine_id >= NUM_ENGINES)
    {
        fprintf(stderr, "Invalid engine ID\n");
        return;
    }

    char message[256];
    snprintf(message, sizeof(message), "ENGINE_ID %d dedicated rpm %d", engine_id, rpm);
    if (engine_sockets[engine_id] != 0)
    {
        send(engine_sockets[engine_id], message, strlen(message), 0);
    }
}

int main()
{
    init_connections();
    send_rpm_all(1000);
    sleep(2);
    send_rpm_to_engine(3, 1500);

    // Close sockets
    for (int i = 0; i < NUM_ENGINES; ++i)
    {
        if (engine_sockets[i] != 0)
        {
            close(engine_sockets[i]);
        }
    }
    return 0;
}
