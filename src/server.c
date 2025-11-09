/**
 * @file server.c
 * @brief Simple TCP server implementation using POSIX sockets.
 *
 * The server listens for incoming connections on a predefined port,
 * receives a message from a connected client, and sends a reply back.
 *
 * It uses helper functions defined in `network.c` for socket creation
 * and data transmission.
 */

#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include "../include/network.h"

/**
 * @brief Main entry point for the TCP server.
 *
 * Workflow:
 *  1. Create and initialize a server socket.
 *  2. Wait for an incoming client connection using `accept()`.
 *  3. Receive a message from the client and print it.
 *  4. Send a simple reply message.
 *  5. Close all sockets and exit.
 *
 * @return int 0 on success, 1 on failure.
 */
int main() {
	// socket creation 
	// binding to port 8080
	// runs liste() so it will wait for clients interaction
	int server_file_descriptor = create_server_socket();
	
	// prepare client address struct 
	struct sockaddr_in client_addr;
	socklen_t addr_len = sizeof(client_addr);

	// blocing call, wait for a client to connect
	int client_file_descriptor = accept(server_file_descriptor, (struct sockaddr*)&client_addr, &addr_len);
	if(client_file_descriptor < 0) {
		perror("Accpet failed");
		return 1;
	}


	printf("Client connected!\n");
	
	//recieves message from client
	char buffer[BUFFER_SIZE];
	recieve_message(client_file_descriptor, buffer);
	printf("From client: %s\n", buffer);
	
	// sends instant reply to client
	const char* reply = "im the server !!!\n";
	send_message(client_file_descriptor, reply);

	//closing file descriptors
	close(server_file_descriptor);
	close(client_file_descriptor);

	printf("connection closed.\n");
	return 0;
}


