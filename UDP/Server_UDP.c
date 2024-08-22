// server program for udp connection
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 6969
#pragma pack(1)
typedef struct
{
    uint8_t data_identifier:1;
    uint8_t packet_identifier;
	uint16_t data;
}packet;

packet packet_data;

char buffer[100];

// Driver code
int main()
{
	int listenfd, len;
	struct sockaddr_in servaddr, cliaddr;
	bzero(&servaddr, sizeof(servaddr));

	// Create a UDP Socket
	listenfd = socket(AF_INET, SOCK_DGRAM, 0);
	// servaddr.sin_addr.s_addr = inet_addr("1.1.1.111");
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_family = AF_INET;

	// bind server address to socket descriptor
	int n=bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	printf("bind %d\n",n);
	
	// receive the datagram
	len = sizeof(cliaddr);
	printf("Waiting for client to send data\n");
	
	while (1)
	{
		printf("data_identifier [%d] : packet_identifier [%d] : data [%d] \n",packet_data.data_identifier,packet_data.packet_identifier,packet_data.data);

		// send the response
		sendto(listenfd,  (void *) &packet_data, sizeof(packet_data), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
		
		int n = recvfrom(listenfd, buffer, sizeof(buffer),0, (struct sockaddr *)&cliaddr, &len); // receive message from server
		
		puts(buffer);
	}
}
