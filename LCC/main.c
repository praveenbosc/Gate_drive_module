#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include "error.h"

// Defined values
#define SERVER_PORT 3003
#define ip "1.1.1.2"

#define PRINTF(args...) \
	do                  \
	{                   \
		printf(args);   \
		fflush(stdout); \
	} while (0);

int readCSV();

typedef struct __attribute__((packed))
{
	uint8_t size;
	uint8_t primary_header;
	uint32_t timestamp;
	uint8_t seq_num;
	uint8_t data;
	uint8_t cmd_num;
	uint8_t data1;
} seq_pkt_body;

typedef struct __attribute__((packed))
{
	uint8_t size;
	uint8_t primary_header;
	uint32_t timestamp;
	uint8_t seq_num;
	uint32_t data;
	uint8_t cmd_num;
	uint32_t data1;
} gim_pkt_body;

seq_pkt_body seq_pkt;
gim_pkt_body gim_pkt;

int flagg = 10;
int sock;
static int i=0;
uint64_t time1()
{
	// Get current epoch time in seconds
	time_t epoch_time = time(NULL);
	uint64_t timestamp = epoch_time;
	return timestamp;
}
int readCSV()
{
	// Read and print each line of the CSV file

	if (flagg == 10)
	{
		seq_pkt.size = 9;
		seq_pkt.primary_header = 2;
		seq_pkt.timestamp = time1();
		seq_pkt.seq_num = 35;
		seq_pkt.data = 0;
		seq_pkt.cmd_num = 36;
		seq_pkt.data1 = 98;

		if (send(sock, &seq_pkt, sizeof(seq_pkt), 0) == -1)
		{
			PRINTF("Sending Failed\n");
			perror("send");
			exit(1);
		}
	}
	gim_pkt.size = 15;
	gim_pkt.primary_header = 2;
	gim_pkt.timestamp = time1();
	gim_pkt.seq_num = 242;
	gim_pkt.data = 11+i;
	gim_pkt.cmd_num = 243;
	gim_pkt.data1 = 40;

	if (send(sock, &gim_pkt, sizeof(gim_pkt), 0) == -1)
	{
		PRINTF("Sending Failed\n");
		perror("send");
		exit(1);
	}
	printf("Sendinggggg \n");

	// if (i == 4)
	// {
	// 	seq_pkt.size = 9;
	// 	seq_pkt.primary_header = 2;
	// 	seq_pkt.timestamp = time1();
	// 	seq_pkt.seq_num = 35;
	// 	seq_pkt.data = 0;
	// 	seq_pkt.cmd_num = 36;
	// 	seq_pkt.data1 = 99;

	// 	if (send(sock, &seq_pkt, sizeof(seq_pkt), 0) == -1)
	// 	{
	// 		PRINTF("Sending Failed\n");
	// 		perror("send");
	// 		exit(1);
	// 	}
	// }
	return 0;
}

int main()
{
	int a = 5;
	// Create the socket

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		perror("socket");
		exit(1);
	}

	// Connect to the server
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = inet_addr(ip);
	while (1)
	{
		if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
		{
			PRINTF("This ip  %s has not permitted to Connect server\n", ip);
			sleep(2);
			continue;
		}

		PRINTF("'%s' client address is Connected to server\n", ip);
		while (1)
		{
			readCSV();
			flagg = 1;
			if(i==4)
			{
				i=0;
			}
			i++;
			sleep(1);
		}
	}
	return 0;
}
