#ifndef NETWORK_H
#define NETWORK_H

#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

// --- server functions ---
int create_server_socket();
int create_client_socket(const char *ip);
void send_message(int sock, const char* msg);
void recieve_message(int sock, char* buffer);

// --- client functions ---

#endif
