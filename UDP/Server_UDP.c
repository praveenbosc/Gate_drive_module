// server program for udp connection
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 6969
#define MAXLINE 1000
// #pragma pack(1)

typedef struct
{
	u_int8_t sof;
	char data[32];
	u_int8_t eof;
} input_data;

// char bin_value[5]={'0','0','1','0','0'};

input_data data;

// int checksum_0=0;

// unsigned char calculateChecksum(unsigned char data_1[], int length)
// {
// 	checksum_0 = 0;
// 	checksum_0 = data_1[0] ^ data_1[1];

// 	for (int i = 2; i < length; i++)
// 	{
// 		checksum_0 = checksum_0 ^ data_1[i];
// 	}
// 	return checksum_0;
// }

// Driver code
int main()
{
	char buffer[100];

	data.sof = 69;
	for (int i = 0; i < 32; i++)
	{
			// data.data[i] = 1;

		if(i == 0)
			data.data[i] = 1;
		else
			data.data[i] = 0;
	}
	data.eof = 16;

	// char message[] = "Hello Client";
	
	// bin_value[0]=1;
	// bin_value[1]=1;
	// bin_value[2]=1;
	// bin_value[3]=0;
	// bin_value[4]=1;

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
		for(int i=0;i<32;i++)
		printf("bin_value [%d] : %d\n",i+1,data.data[i]);

		// send the response
		sendto(listenfd,  (void *) &data, sizeof(data), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
		
		int n = recvfrom(listenfd, buffer, sizeof(buffer),
						 0, (struct sockaddr *)&cliaddr, &len); // receive message from server
		buffer[n] = '\0';
		puts(buffer);

		// // send the response
		// sendto(listenfd, (void *)&buffer, sizeof(buffer), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
	}
}
