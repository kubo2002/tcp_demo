/**
 * @file client.c
 * @brief Simple TCP client implementation using POSIX sockets.
 *
 * The client connects to a TCP server on a predefined port,
 * sends a message, and waits for a reply.
 *
 * It uses helper functions defined in `network.c` for socket creation
 * and data transfer.
 */

#include <stdio.h>
#include <unistd.h>
#include "../include/network.h"

/**
 * @brief Main entry point for the TCP client.
 *
 * Workflow:
 *  1. Create a client socket and connect to the server.
 *  2. Send a message to the server.
 *  3. Wait for a response from the server.
 *  4. Display the received message.
 *  5. Close the socket and exit.
 *
 * @return int 0 on success, 1 on failure.
 */

int main() {
    // connect to the server
    const char *server_ip = "127.0.0.1"; // local server (localhost)
    int sock = create_client_socket(server_ip);

    // prepare a message to send
    const char *message = "Hello from client";
    send_message(sock, message);
    printf("Sent to server: %s\n", message);

    // receive server response
    char buffer[BUFFER_SIZE];
    receive_message(sock, buffer);
    printf("From server: %s\n", buffer);

    // close the socket
    close(sock);
    printf("Connection closed.\n");

    return 0;
}

