// User defined ip and port
#include "tcp.h"
#pragma pack(1)
#define SERVER_IP "127.0.0.1"
#define PORT_0 8003
#define PORT_1 8004

// Function Declaration
void motor_controller();
void receiving_data_port_0();
void receiving_data_port_1();
int send_packet();
static FUNC_STATUS connect_to_channels(const char *ip, network_info_t* conn_info,int* conn_status);
static FUNC_STATUS disconnect_to_channels(network_info_t *conn_info, int *conn_status);
static FUNC_STATUS handle_seq_command(internal_cmd_t *r_cmd_data);
// void recovery_loop_to_snd_data();
static FUNC_STATUS mq_init();
static FUNC_STATUS rcv_data_mq();

// User defined structure
typedef struct 
{
	uint8_t start_of_frame;
	uint8_t packet_identifier;
	uint16_t data;
	uint8_t checksum;
} Send_packet; // typecast as a Send_packet and avoid structure padding.

typedef struct
{
	uint8_t start_of_frame;
	uint8_t data[14];
	uint8_t checksum;
} Receive_packet; // typecast as a Receive_Packet and avoid structure padding.

// typedef struct
// {
// 	uint8_t data_identifier;
// 	int data;
// }snd_raw_data __attribute__((packed)); // typecast as a Send_packet and avoid structure padding.


