/**
 ******************************************************************************
 * @file			motor_controller.c
 * @project         Gate_Driver_Module.
 * @brief			It will recv cmd from sequencer based on it will connect or disconect to respection module ( 2CH_Waveshare_eth_to_uart_device )
 * 					After connection the status will update (Through enum) and based on it will send or recv data.
 * 					In PORT_0 sending and recv data , In PORT_1 recv data.
 * 					Note : when data has fail to send the respective module ( It will try to send only five times continuesly it will not possible means it will exit)
 * @author			Praveen_Bosco
 * @version			v1.0
 * @ref	            readme.txt -> Code/include/Gate_driver_module/readme.txt.
 ******************************************************************************
 **/
#include <arpa/inet.h> //Including required header file
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include "error.h"
#include "tcp.h"
#include "ec.h"
#include "debugLogs.h"
#include "Gate_drive_module/motor_controller_1.h"

#define NUM_OF_CHANNEL 1 // Initialize number of channels to be connected
#define max_size 5

#define BUFFER_SIZE 16

unsigned char calculateChecksum(unsigned char data_1[], int length);

static const int port[NUM_OF_CHANNEL] = {2000}; // Initialize port numbers

struct mq_attr g_attr_1;				  // Initialize object for message queue structure
static mqd_t g_mq_etx_to_mc_1 = (mqd_t)0; // creating message queue file discripter
static mqd_t g_seq_to_motor_cntrl_1 = (mqd_t)0;

snd_raw_data g_snd_data[max_size];
static counter = 0;
int ret_value = 0;
unsigned char checksum_0 = 0;

network_info_t g_motor_cntrl_conn[NUM_OF_CHANNEL]; // Initialize object for socket file discripter structure

static int g_conn_status = 0;
enum // Declaring connection status enum
{
	EMC_DISCONNECTED = 0,
	EMC_CONNECTED = 1,
	// RESEND_DATA = 2,
};

static int g_MC_connection_status[sizeof(port) / sizeof(int)] = {EMC_DISCONNECTED}; // Declaring connection status variable
static int g_rcv_status;

void motor_controller() // The operation starts here.
{
	if (log_init("[MC]", PRINT_ALL, LOG_TO_STDOUT, NULL) != 1) // Initialize log function.
	{
		LOG_PRINT(PRINT_ERROR, "FM CSV failed\n");
		return NULL;
	}

	LOG_PRINT(PRINT_INFO, "**Gate_Driver_Module_Process**\t[ Child ]\t-\tPID : [ %d ]\n", getpid()); // getting pid

	if (mq_init() == FAILURE) // Initialize all message queues fn call.
	{
		LOG_PRINT(PRINT_ERROR, "Message Queue Init Failed\n");
		return FAILURE;
	}

	pthread_t thread_id; // Start a thread

	pthread_create(&thread_id, NULL, receiving_data_port_0, NULL); // Create the thread to handle the receiving_data_port_0 data.
	pthread_detach(thread_id);

	pthread_create(&thread_id, NULL, receiving_data_port_1, NULL); // Create the thread to handle the receiving_data_port_1 data.
	pthread_detach(thread_id);

	rcv_data_mq();
}

static FUNC_STATUS mq_init() // Initialize all message queues.
{
	/**< MQ to send "DATA" to Motor Control process */
	if ((g_mq_etx_to_mc_1 = mqueue_init(MQ_ETHRX_TO_MOTOR_CONTROLLER, MQ_READ, &g_attr_1)) == FAILURE)
	{
		LOG_PRINT(PRINT_ERROR, "MQ_ETHRX_TO_MOTOR_CONTROLLER init Failed\n");
		return FAILURE;
	}
	/**< MQ to send "SEQ_CMD" to Motor Control process */
	if ((g_seq_to_motor_cntrl_1 = mqueue_init(MQ_SEQ_TO_MOTOR_CONTROLLER, O_CREAT | O_RDONLY, &g_attr_1)) == FAILURE)
	{
		LOG_PRINT(PRINT_ERROR, "MQ_SEQ_TO_MOTOR_CONTROLLER init Failed\n");
		return FAILURE;
	}
}

static FUNC_STATUS rcv_data_mq()
{
	while (1)
	{
		fd_set set;
		FD_ZERO(&set);
		FD_SET(g_mq_etx_to_mc_1, &set);
		FD_SET(g_seq_to_motor_cntrl_1, &set);

		int retval = select(__FD_SETSIZE, &set, NULL, NULL, NULL);

		if (retval == -1)
		{
			LOG_PRINT(PRINT_ERROR, "Select Failed with error %d\n", errno);
			raise_fault(ERR_PR_ETHTR_IPC_FAIL);
			sleep(2); /**< Need this incase this select function goes crazy. */
			continue;
		}

		if (FD_ISSET(g_seq_to_motor_cntrl_1, &set) == true)
		{
			internal_cmd_t cmd_data; // creating objects for struture

			if (mqueue_receive(g_seq_to_motor_cntrl_1, (char *)&cmd_data, g_attr_1) == FAILURE) // wait to receive the seq_cmd from eth-rx in BLOCKING MOOD
			{
				LOG_PRINT(PRINT_ERROR, "Reading from sequencer ipc failed, errno = %d\n", errno);
				return FAILURE;
			}
			handle_seq_command(&cmd_data);
		}

		if (FD_ISSET(g_mq_etx_to_mc_1, &set) == true)
		{

			if (mqueue_receive(g_mq_etx_to_mc_1, (char *)&g_snd_data[counter], g_attr_1) == FAILURE) // wait to receive the data from eth-rx in BLOCKING MOOD
			{
				LOG_PRINT(PRINT_ERROR, "Reading from sequencer ipc failed, errno = %d\n", errno);
				return FAILURE;
			}

			if (g_MC_connection_status[0] == EMC_CONNECTED) // if its in connected to server means it will send Packtized data [ CLIENT TO SERVER ]
			{
				ret_value = send_packet();

				if (ret_value == -1)
				{
					/**< No connection to FC was found. */
					LOG_PRINT(PRINT_ERROR, "Send to MC ( SEND TO SERVER ) has failed, please resend the data\\n");
					// g_conn_status == RESEND_DATA;
				}
			}
			else
			{
				/**< No connection to FC was found. */
				LOG_PRINT(PRINT_ERROR, "Send to MC has CC_Failed\n");
				// g_conn_status = RESEND_DATA;
				LOG_PRINT(PRINT_INFO, "g_conn_status %d\n", g_conn_status);
			}
			
			counter++; // It has 5 bytes of capacity only it has

			if ((ret_value == 2)||(counter == 4)) // Once could not able to send the data it will over written after 5 times
			{
				counter = 0;  // for safer side 
			}
		}
	}
}

static FUNC_STATUS handle_seq_command(internal_cmd_t *r_cmd_data) // It will handle_seq_command connect or disconnect from server
{
	LOG_PRINT(PRINT_INFO, "RECEIVED_SEQ_CMD: %d\n", r_cmd_data->cmd);

	switch (r_cmd_data->cmd) // It will checking the received cmds based on it choose the operation connect or disconnect.
	{
	case EC_CMD_MOTOR_CNTRL_CONN:
	{
		connect_to_channels(SERVER_IP, g_motor_cntrl_conn, g_MC_connection_status); // It will connect to all channles and getting connection status and fd.
		break;
	}
	case EC_CMD_MOTOR_CNTRL_DISCONN:
	{
		disconnect_to_channels(g_motor_cntrl_conn, g_MC_connection_status); // It will connect to all channles and getting disconnection status.
		break;
	}
	default:
	{
		LOG_PRINT(PRINT_ERROR, "UNKNOWN_SEQ_CMD_RECEIVED : %d\n", r_cmd_data->cmd); // UNKNOWN_SEQ_CMD_RECEIVED
		return FAILURE;
	}
	}
	return SUCCESS;
}

static FUNC_STATUS connect_to_channels(const char *ip, network_info_t *conn_info, int *conn_status) // It will connect to all channles and getting disconnection status.
{
	network_info_t network_info[NUM_OF_CHANNEL] = {0}; // creating objects for struture

	for (int i = 0; i < NUM_OF_CHANNEL; i++)
	{
		network_info[i].sock = -1; // Set to invalid socket fd.

		if (connect_to_server(&network_info[i], ip, (uint16_t)port[i]) == FAILURE) // Connect to the server.
		{
			LOG_PRINT(PRINT_INFO, "Connection has failed, errno = %d, index = %d, ip: %s\n", errno, i, ip);

			close(network_info[i].sock); // Close the socket.
			sleep(2);
			continue;
		}
		else
		{
			conn_info[i].sock = network_info[i].sock; // assign value to another variable and updating connection status
			conn_status[i] = EMC_CONNECTED;
			LOG_PRINT(PRINT_INFO, "Connected to %s at index = %d, sock = %d\n", ip, i, network_info[i].sock);
		}
		sleep(2);
	}
	return SUCCESS;
}

static FUNC_STATUS disconnect_to_channels(network_info_t *conn_info, int *conn_status) // It will connect to all channles and getting disconnection status.
{
	for (int i = 0; i < NUM_OF_CHANNEL; i++)
	{
		// if (conn_status[i] == EMC_CONNECTED) // Call Close only if the current state is connected.
		// {
		close(conn_info[i].sock);
		LOG_PRINT(PRINT_INFO, "Disconnecting from server, index = %d, sock = %d\n", i, conn_info[i].sock);
		// }
		conn_info[i].sock = -1;
		conn_status[i] = EMC_DISCONNECTED; // assign value to another variable and updating disconnection status
	}
	return SUCCESS;
}


Send_packet packets[5];
int temp = 0; // creating temp variable.

int send_packet()
{
	static int l_counter_s = 0;
	for (int i = 0, j = 0; i < max_size; i++, j++)
	{
		if (g_snd_data[i].data_identifier != 0)
		{
			LOG_PRINT(PRINT_INFO, "SEQ->[%d,%d]\n", g_snd_data[i].data_identifier, g_snd_data[i].data);

			packets[j].start_of_frame = 254; // Assigning value to the structure variable.

			packets[j].packet_identifier = g_snd_data[i].data_identifier;

			temp = g_snd_data[i].data;

			// Convert decimal to hexadecimal and store it in hex variable
			sprintf(packets[j].data, "%X", temp);

			// Calculating Checksum
			packets[j].checksum = 0;

			packets[j].checksum ^= packets[j].start_of_frame;
			packets[j].checksum ^= packets[j].packet_identifier;
			packets[j].checksum ^= packets[j].data;

			LOG_PRINT(PRINT_INFO, "\nstart_of_frame %d : packet_identifier %d : data %d :checksum %d\n\n", packets[j].start_of_frame, packets[j].packet_identifier, packets[j].data, packets[j].checksum);

			// Send packetized data to server
			if ((send(g_motor_cntrl_conn[0].sock, &packets, sizeof(Send_packet), 0)) < 0) // It will print error message (want to exit/continue)
			{
				LOG_PRINT(PRINT_ERROR, "SEND TO SERVER failed\n");
				i--; 	// for trying to send the unsend data for 5 times , after it could not done means it will terminate the loop
				j--;

				if (l_counter_s == 5)	// lost_counter
				{
					g_snd_data[i].data_identifier = 0;
					return -1;
				}
				l_counter_s++;
				usleep(10000);

				continue;
			}
			LOG_PRINT(PRINT_INFO, "***SEND TO SERVER***\n");

			g_snd_data[i].data_identifier = 0;
		}
		usleep(10000);
	}
	return 2;
}

void receiving_data_port_0() // Receiving data to to Motor Control process.
{
	Receive_packet recv_pkt_0; // creating objects for struture
	unsigned char buffer[BUFFER_SIZE] = {0};
	unsigned char checksum = 0;
	// FILE *fp1;
	// fp1 = fopen("SEND_RCV.csv", "w"); // creating file pointer and open a file in write mood
	int bytes_rcv = 0; // creating temp variable
	while (1)
	{
		LOG_PRINT(PRINT_INFO, "[ port_0 ] while\n");
		if (g_MC_connection_status[0] == EMC_CONNECTED) // It will recv data when it will connected mood [ CLIENT TO SERVER ]
		{
			LOG_PRINT(PRINT_INFO, "Receiving [ port_0 ] started succesfully\n");

			bytes_rcv = 0;

			while ((bytes_rcv = recv(g_motor_cntrl_conn[0].sock, (void *)buffer, sizeof(buffer), 0)) > 0)
			{
				// Receive data from client
				if (bytes_rcv < 0)
				{
					perror("*****Read_ERROR*****");
					exit(EXIT_FAILURE);
				}

				// If received data is 254, store it to data variable
				if (buffer[0] == 254)
				{
					memcpy(&recv_pkt_0, &buffer, sizeof(recv_pkt_0));

					checksum = calculateChecksum((void *)&recv_pkt_0, sizeof(recv_pkt_0) - 1);

					if ((int8_t)checksum == recv_pkt_0.checksum)
					{
						printf("\nchks %d, data[15] %d\n", (int8_t)checksum, recv_pkt_0.checksum);

						printf("Data received: ");

						for (int i = 0; i < sizeof(recv_pkt_0); i++)
						{
							printf("%u ", recv_pkt_0.data[i]);
						}
						printf("\n");
					}
				}
				memcpy(&recv_pkt_0, "0", sizeof(recv_pkt_0));
			}
		}
	}
	// fclose(fp1);
	return NULL; // returning null value
}

// Function definition for reading the data from the module.
void receiving_data_port_1() // Receiving data to to Motor Control process.
{
	Receive_packet recv_pkt_1; // creating objects for sn the interim I'll just keep my fingers crossed"truture
	unsigned char checksum_1 = 0;
	unsigned char buffer_1[BUFFER_SIZE] = {0};
	// FILE *fp;
	// fp = fopen("RECEIVE_ONLY.csv", "w+"); // creating file pointer and open a file in write mood
	int bytes_received_rcv = 0; // creating temp variable
	while (1)
	{
		LOG_PRINT(PRINT_INFO, "[ port_1 ] while\n");
		if (g_MC_connection_status[1] == EMC_CONNECTED) // It will recv data when it will connected mood [ CLIENT TO SERVER ]
		{
			LOG_PRINT(PRINT_INFO, "Receiving [ port_1 ] started succesfully\n");

			bytes_received_rcv = 0;

			while ((bytes_received_rcv = recv(g_motor_cntrl_conn[0].sock, (void *)buffer_1, sizeof(buffer_1), 0)) > 0)
			{
				// Receive data from client
				if (bytes_received_rcv < 0)
				{
					perror("####READ_ERROR 1####");
					exit(EXIT_FAILURE);
				}

				// If received data is 254, store it to data variable
				if (buffer_1[0] == 254)
				{
					memcpy(&recv_pkt_1, &buffer_1, sizeof(recv_pkt_1));

					checksum_1 = calculateChecksum((void *)&recv_pkt_1, sizeof(recv_pkt_1) - 1);

					if ((int8_t)checksum_1 == recv_pkt_1.checksum)
					{
						printf("\nchks %d, data[15] %d\n", (int8_t)checksum_1, recv_pkt_1.checksum);

						printf("Data received: ");

						for (int i = 0; i < sizeof(recv_pkt_1); i++)
						{
							printf("%u ", recv_pkt_1.data[i]);
						}
						printf("\n");
					}
				}
				memcpy(&recv_pkt_1, "0", sizeof(recv_pkt_1));
			}
		}
	}
	// fclose(fp);
	return NULL; // returning null value
}

unsigned char calculateChecksum(unsigned char data_1[], int length)
{
	checksum_0 = 0;
	checksum_0 = data_1[0] ^ data_1[1];

	for (int i = 2; i < length; i++)
	{
		checksum_0 = checksum_0 ^ data_1[i];
	}
	return checksum_0;
}




























// void recovery_loop_to_snd_data()
// {
// 	LOG_PRINT(PRINT_INFO, "[ recovery_loop_to_snd_data ] \n");
// 	static int l_counter =0;
// 	while (1)
// 	{
// 		if (g_conn_status == RESEND_DATA && g_MC_connection_status[0] == EMC_CONNECTED) // It will recv data when it will connected mood [ CLIENT TO SERVER ]
// 		{
// 			LOG_PRINT(PRINT_INFO, "[ EMC_CONNECTED_ recovery_loop_to_snd_data ] \n");
// 			ret_value_1 = send_packet();

// 			if (ret_value_1 == -1)
// 			{
// 				LOG_PRINT(PRINT_ERROR, "{ g_MC_connection_status[0] -->> sending failed Please close the connection and reconnect it } \n");
// 				if(l_counter == 2)
// 				{
// 					disconnect_to_channels(g_motor_cntrl_conn, g_MC_connection_status);
// 				}
// 				l_counter++;
// 				sleep(2);
// 			}
// 			else if(ret_value_1 == 2)
// 			{
// 				g_conn_status = 0; 
// 			}
// 		}
// 		else if (g_conn_status == RESEND_DATA && g_MC_connection_status[0] == EMC_DISCONNECTED)
// 		{
// 			LOG_PRINT(PRINT_ERROR, "[ g_MC_connection_status[0]->> Connection not establisbed ] \n");
// 			disconnect_to_channels(g_motor_cntrl_conn, g_MC_connection_status);
// 			sleep(2);
// 			connect_to_channels(SERVER_IP, g_motor_cntrl_conn, g_MC_connection_status);
// 			sleep(2);
// 		}
// 	sleep(2);
// 	}
// }

//CIRCULAR LINKED LIST ITS WORKING IN CONDITION.
// // Node structure
// struct Node
// {
//     snd_raw_data data; // Change data type to snd_raw_data
//     struct Node *next;
// };

// // Array to hold nodes
// struct Node arr[SIZE];

// // Function to create a new node
// struct Node *createNode(int data_identifier, int data)
// {
//     struct Node *newNode = NULL;
//     // Index to overwrite the data from the first node if necessary
//     static int overwrite_index = 0;
//     for (int i = 0; i < SIZE; i++)
//     {
//         if (arr[i].data.data == 0)
//         {   // Check if slot is available
//             arr[i].data.data_identifier = data_identifier;
//             arr[i].data.data = data;
//             arr[i].next = NULL;
//             newNode = &arr[i];
//             break;
//         }
//     }
//     if (newNode==NULL)
//     {
//          // Check if this is the first filled slot to track for overwriting
//             arr[overwrite_index].data.data_identifier = data_identifier;
//             arr[overwrite_index].data.data = data;
//             newNode = &arr[overwrite_index];

//             if(overwrite_index == 4)
//             {
//                 overwrite_index = 0;
//                 return newNode;
//             }
//             overwrite_index++;
//     }
//     return newNode;
// }

// // Function to insert a node at the end of the circular linked list
// void insertNode(struct Node **head, int data_identifier, int data)
// {
//     struct Node *newNode = createNode(data_identifier, data);
//     if (*head == NULL)
//     {
//         *head = newNode;
//         newNode->next = *head;
//     }
//     else
//     {
//         struct Node *temp = *head;
//         while (temp->next != *head)
//         {
//             temp = temp->next;
//         }
//         temp->next = newNode;
//         newNode->next = *head;
//     }
// }

// // Function to display the circular linked list
// void displayList(struct Node *head)
// {
//     int rt_value=0;
//     if (head == NULL)
//     {
//         printf("List is empty.\n");
//         return;
//     }
//     struct Node *temp = head;
//     do
//     {
//         LOG_PRINT(PRINT_INFO,"\n[In Recovery Loop] -->> (%d, %d)\n",temp->data.data_identifier, temp->data.data);
//         temp = temp->next;

//          	if (g_MC_connection_status[0] == EMC_CONNECTED) // It will recv data when it will connected mood [ CLIENT TO SERVER ]
// 			{
//                 rt_value = 0;
// 				rt_value = send_packets(&temp);
// 				if(rt_value == -1)
// 				{
// 					LOG_PRINT(PRINT_ERROR,"{ g_MC_connection_status[0] -->> sending failed Please close the connection and reconnect it } \n");
// 				}
// 				else if(rt_value == 2)
// 				{
// 					break;
// 				}
// 			}
// 			else
// 			{
// 				LOG_PRINT(PRINT_ERROR,"[ g_MC_connection_status[0]->> Connection not establisbed ] \n");
// 				disconnect_to_channels(g_motor_cntrl_conn, g_MC_connection_status);
// 				sleep(2;
//                 connect_to_channels(SERVER_IP, g_motor_cntrl_conn, g_MC_connection_status);
// 				sleep(2;
// 			}
//     } while (temp != head);
// }

// void resend_loop(snd_raw_data r_data)
// {
//     struct Node *head = NULL;

//     // Creating 10 nodes (overwriting the first one)
//     insertNode(&head, r_data.data_identifier, r_data.data);

//     // Displaying the circular linked list
//     printf("Circular Linked List: ");
//     displayList(head);

//     printf("\n");

//     return 0;
// }
