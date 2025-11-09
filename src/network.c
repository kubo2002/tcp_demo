#include <complex.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/network.h"

/**
 * @file network.c
 * @brief Implementation of basic TCP networking functions.
 *
 * This module provides simple abstractions for creating
 * TCP server and client sockets, as well as sending and receiving
 * messages through established connections.
 */

/**
 * @brief Creates and initializes a TCP server socket.
 *
 * This function:
 *  - Creates a new IPv4 TCP socket.
 *  - Binds it to a predefined port (PORT).
 *  - Puts it into listening mode, allowing incoming client connections.
 *
 * @return int File descriptor of the created server socket.
 * @note The returned socket should later be passed to `accept()` to handle clients.
 * @warning Exits the program on failure.
 */
int create_server_socket() {
	
	int server_file_descriptor;
	struct sockaddr_in address;

	// socket creation
	server_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (server_file_descriptor < 0) {
		perror("Socket failure");
		exit(EXIT_FAILURE);
	}

	// adress struct init
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// binding the socket on port
	if (bind(server_file_descriptor, (struct sockaddr*)&address, sizeof(address)) < 0) {
		perror("Listening failure");
		exit(EXIT_FAILURE);
	}
	
	// listening activation
	if(listen(server_file_descriptor, 3) < 0) {
		perror("Listening failure");
		exit(EXIT_FAILURE);
	}

	printf("Server listening on port %d : \n", PORT);

	return server_file_descriptor;	
}

/**
 * @brief Creates and connects a TCP client socket to a given IP address.
 *
 * This function:
 *  - Creates a new IPv4 TCP socket.
 *  - Converts the given IP string into binary form.
 *  - Connects to the server running on the specified address and port.
 *
 * @param ip String representing the server IP address (e.g. "127.0.0.1").
 * @return int File descriptor of the connected client socket.
 * @warning Exits the program on failure.
 */
int create_client_socket(const char *ip) {
    	int sock;
    	struct sockaddr_in serv_addr;

    	// Create an IPv4 TCP socket
    	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        	perror("Socket creation failed");
        	exit(EXIT_FAILURE);
    	}


    	serv_addr.sin_family = AF_INET;
    	serv_addr.sin_port = htons(PORT);

    
    	// Convert IP address from string to binary form
    	if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
        	perror("Invalid address");
        	exit(EXIT_FAILURE);
    	}

    	// Attempt to connect to the server
    	if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        	perror("Connection failed");
        	exit(EXIT_FAILURE);
    	}

    	printf("Connected to server at %s:%d\n", ip, PORT);
    	return sock;
}

/**
 * @brief Sends a text message over a connected socket.
 *
 * @param sock File descriptor of the socket to send data through.
 * @param msg Null-terminated string containing the message to send.
 * @note The message is sent as a single TCP packet; no delimiter is appended.
 */
void send_message(int sock, const char *msg) {
	
	if (send(sock, msg, strlen(msg), 0) < 0) {
        	perror("send failed");
    	}
}

/**
 * @brief Receives a text message from a connected socket.
 *
 * @param sock File descriptor of the socket to read data from.
 * @param buffer Pointer to a buffer where the received message will be stored.
 *
 * @note This function blocks until data is received.
 * @warning If the connection is closed by the peer, an empty string is returned.
 */
void receive_message(int sock, char *buffer) {

    	memset(buffer, 0, BUFFER_SIZE);

    
    	ssize_t bytes_read = read(sock, buffer, BUFFER_SIZE - 1);

    	if (bytes_read < 0) {
        	perror("Read failed");
    	} else if (bytes_read == 0) {
        	printf("Connection closed by peer.\n");
    	}
}



