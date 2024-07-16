// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <arpa/inet.h>

// void control_motor(int motor_id, int rpm)
// {
//     // Dummy function to control the motor
//     printf("Motor %d set to RPM %d\n", motor_id, rpm);
// }

// void handle_message(char *message)
// {
//     int rpm;
//     int engine_id;

//     if (sscanf(message, "ENGINE_ID %d Common rpm %d",&engine_id, &rpm) == 1)
//     {
//         printf("message :\"%s\"\n",message);
//         control_motor(1, rpm);
//         control_motor(2, rpm);
//     }
//     else if (sscanf(message, "ENGINE_ID %d dedicated rpm %d", &engine_id, &rpm) == 2)
//     {
//         printf("message :\"%s\"\n",message);
//         control_motor(1, rpm);
//         control_motor(2, rpm);
//     }
//     else
//     {
//         fprintf(stderr, "Invalid message format\n");
//     }
// }

// int main(int argc, char *argv[])
// {
//     if (argc != 2)
//     {
//         fprintf(stderr, "Usage: %s <port>\n", argv[0]);
//         return EXIT_FAILURE;
//     }

//     int port = atoi(argv[1]);
//     int server_fd, new_socket;
//     struct sockaddr_in address;
//     int addrlen = sizeof(address);
//     char buffer[1024] = {0};

//     // Creating socket file descriptor
//     if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
//     {
//         perror("Socket failed");
//         exit(EXIT_FAILURE);
//     }

//     // Bind the socket to the network address and port
//     address.sin_family = AF_INET;
//     address.sin_addr.s_addr = INADDR_ANY;
//     address.sin_port = htons(port);

//     if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
//     {
//         perror("Bind failed");
//         close(server_fd);
//         exit(EXIT_FAILURE);
//     }

//     // Listen for incoming connections
//     if (listen(server_fd, 3) < 0)
//     {
//         perror("Listen failed");
//         close(server_fd);
//         exit(EXIT_FAILURE);
//     }

//     printf("Server is listening on port %d\n", port);

//     // Accept incoming connection
//     if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
//     {
//         perror("Accept failed");
//         close(server_fd);
//         exit(EXIT_FAILURE);
//     }

//     printf("Connection accepted\n");

//     // Read and handle messages from the client
//     while (1)
//     {
//         int valread = read(new_socket, buffer, 1024);
//         if (valread > 0)
//         {
//             buffer[valread] = '\0';
//             handle_message(buffer);
//         }
//         else if (valread < 0)
//         {
//             perror("Read failed");
//             break;
//         }
//     }

//     close(new_socket);
//     close(server_fd);
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void control_motor(int motor_id, int rpm) {
    // Dummy function to control the motor
    printf("Motor %d set to RPM %d\n", motor_id, rpm);
}

void handle_message(char *message) {
    int rpm;
    int engine_id;

    if (sscanf(message, "ENGINE_ID %d Common rpm %d", &engine_id, &rpm) == 2) {
        printf("Received message: \"%s\"\n", message);
        control_motor(1, rpm);
        control_motor(2, rpm);
    } else if (sscanf(message, "ENGINE_ID %d dedicated rpm %d", &engine_id, &rpm) == 2) {
        printf("Received message: \"%s\"\n", message);
        control_motor(1, rpm);
        control_motor(2, rpm);
    } else {
        fprintf(stderr, "Invalid message format\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int port = atoi(argv[1]);
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to the network address and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", port);

    // Accept incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Connection accepted\n");

    // Read and handle messages from the client
    while (1) {
        int valread = read(new_socket, buffer, 1024);
        if (valread > 0) {
            buffer[valread] = '\0';
            handle_message(buffer);
        } else if (valread < 0) {
            perror("Read failed");
            break;
        }
    }

    close(new_socket);
    close(server_fd);
    return 0;
}
