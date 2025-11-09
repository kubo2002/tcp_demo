# TCP Client-Server Demo in C

A simple and modular implementation of a **TCP client-server communication system** in C using **POSIX sockets**.  
This project demonstrates fundamental networking concepts such as socket creation, connection handling, and message exchange over TCP/IP.

---

## Features

- **Server**
  - Listens for incoming TCP connections on a predefined port.
  - Accepts one client connection and receives a message.
  - Sends a reply message back to the client.
  
- **Client**
  - Connects to the server using a given IP address.
  - Sends a custom message.
  - Waits for a reply and displays it in the console.
  
- **Modular Design**
  - `network.c / network.h` handle all low-level socket operations.
  - `server.c` and `client.c` only contain high-level logic.
  - Easily extendable for multi-client support or protocol expansion.
 
## Build Instructions

### Requirements
- GCC or Clang compiler  
- Linux or macOS (POSIX environment)  
- `make` utility

### Compile

```bash
make
```
This will produce :

```bash
bin/server
bin/client
```
## Run the Demo

### Start the server
```bash
make run-server
```
Expected output:

```bash
Server listening on port 8080...
Client connected!
From client: Hello from client
```
### In another terminal run the client

```bash
make run-client
```
Expected output:

```bash
Connected to server at 127.0.0.1:8080
From server: I am the server !!!
```

## How it works
1. The server creates a socket (`socket()`), binds it to a port (`bind()`), and waits for connections (`listen()`).

2. The client connects to the server using `connect()`.

3. Both communicate using `send()` and `read()`.

4. When done, both sides close their sockets gracefully using `close()`.

## Future Plans
This project is still in development. Planned features:
    - Support for multiple clients (via `fork()` or `select()`)
    - Logging system for server messages
    - Command-line arguments for IP/port configuration
    - Graceful signal handling (`SIGINT`)

# Author
## Jakub Gubány
gubanyj.jakub@gmail.com
github.com/kubo2002
