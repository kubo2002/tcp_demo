# --- Compile options ---
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

# --- Basic project structure settings for my project ---

BIN_DIR = bin
SRC_DIR = src

# --- Source ---

SERVER_SRC = $(SRC_DIR)/server.c $(SRC_DIR)/network.c
CLIENT_SRC = $(SRC_DIR)/client.c $(SRC_DIR)/network.c

SERVER_BIN = $(BIN_DIR)/server
CLIENT_BIN = $(BIN_DIR)/client

# Target
all: $(SERVER_BIN) $(CLIENT_BIN)

$(SERVER_BIN): $(SERVER_SRC)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ # not really sure if this will work

$(CLIENT_BIN): $(CLIENT_SRC)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

run-server: $(SERVER_BIN)
	./$(SERVER_BIN)

run-client: $(CLIENT_BIN)
	./$(CLIENT_BIN)

#-- clear
clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean run-server run-client

