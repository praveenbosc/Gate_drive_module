// // udp client driver program 
// #include <stdio.h> 
// #include <strings.h> 
// #include <sys/types.h> 
// #include <arpa/inet.h> 
// #include <sys/socket.h> 
// #include<netinet/in.h> 
// #include<unistd.h> 
// #include<stdlib.h> 

// #define PORT 6969 
// #define MAXLINE 1000 

// typedef struct
// {
// 	int sof;
// 	int data[32];
// 	int eof;
// } input_data;

// input_data data , data_1;

// // Driver code 
// int main() 
// { 

// int checksum_0=0;

// 	data.sof = 69;
// 	for (int i = 0; i < 32; i++)
// 	{
// 		data.data[i] = i + 1;
// 	}
// 	data.eof = 169;

// 	char buffer[100]; 
// 	char *message = "HELLO"; 
// 	int sockfd, n; 
// 	struct sockaddr_in servaddr; 
	
// 	// clear servaddr 
// 	bzero(&servaddr, sizeof(servaddr)); 
// 	servaddr.sin_addr.s_addr = INADDR_ANY; 
// 	servaddr.sin_port = htons(PORT); 
// 	servaddr.sin_family = AF_INET; 
	
// 	// create datagram socket 
// 	sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
	
// 	// connect to server 
// 	if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) 
// 	{ 
// 		printf("\n Error : Connect Failed \n"); 
// 		exit(0); 
// 	} 

// 	// request to send datagram 
// 	// no need to specify server address in sendto // connect stores the peers IP and port
	
// 	// waiting for response 
// 	// if(recvfrom(sockfd, (void*) &data_1, sizeof(data_1), 0, (struct sockaddr*)NULL, NULL) > 0)
// 	// { 
// 	// 	printf("SOF : %d\n",data_1.sof); 
// 	// 	for (int i = 0; i < 31; i++)
// 	// 	{
// 	// 		printf("Data [%d]: %d\t",i,data_1.data[i]);
// 	// 	}
// 	// 	printf("\nEOF : %d",data_1.eof); 
// 	// }
// 	int x=0;
// 	while(1)
// 	{
// 	printf("while\n");
	
// 	x=sendto(sockfd,message, sizeof(message), 0, (struct sockaddr*)NULL, sizeof(servaddr)); 
// 	if(x > 0)
// 		printf("rcv : %d\n",x);
// 	// x=recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)NULL, NULL) ;
// 	// printf("rcv : %d\n",x);
// 	// puts(buffer);
// 	usleep(10000);
// 	}
	
// 	// close the descriptor 
// 	close(sockfd); 
// } 
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


