CC = gcc

OBJ_DIR = ./build/
BASH_SRC_DIR = ./serversrc/bash/*/
BASH_OBJ_DIR = ./build/bash/

SERVER_INCLUDES = -I serversrc/bash/includes/
CLIENT_INCLUDES = -I clientsrc/includes/

SERVER_CFLAGS = -lpthread -lreadline -o
CLIENT_CFLAGS = -lreadline -o

BASH_SRC = $(wildcard $(BASH_SRC_DIR)*.c)
BASH_OBJ = $(patsubst $(BASH_SRC_DIR)%.c, $(BASH_OBJ_DIR)%.o, $(BASH_SRC))

all: server client

server: $(OBJ_DIR)server.o $(OBJ_DIR)logger.o $(OBJ_DIR)send_read_msg.o
	$(CC) $(SERVER_INCLUDES) $(BASH_OBJ) $(OBJ_DIR)logger.o $(OBJ_DIR)server.o $(OBJ_DIR)send_read_msg.o $(SERVER_CFLAGS) server
$(OBJ_DIR)server.o: serversrc/server.c
	$(CC) -c serversrc/server.c -o $(OBJ_DIR)server.o
$(BASH_OBJ_DIR)%.o: $(BASH_SRC_DIR)%.c
	$(CC) -c $< -o $@


client: $(OBJ_DIR)client.o $(OBJ_DIR)init_client.o $(OBJ_DIR)logger.o $(OBJ_DIR)send_read_msg.o
	$(CC) $(CLIENT_INCLUDES) $(OBJ_DIR)client.o $(OBJ_DIR)init_client.o $(OBJ_DIR)logger.o $(OBJ_DIR)send_read_msg.o $(CLIENT_CFLAGS) client
$(OBJ_DIR)client.o: clientsrc/client.c logger/logger.h
	$(CC) -c clientsrc/client.c -o $(OBJ_DIR)client.o
$(OBJ_DIR)init_client.o: clientsrc/init_client.c
	$(CC) -c clientsrc/init_client.c -o $(OBJ_DIR)init_client.o


$(OBJ_DIR)logger.o: logger/logger.c logger/logger.h
	$(CC) -c logger/logger.c -o $(OBJ_DIR)logger.o
$(OBJ_DIR)send_read_msg.o: utils/send_read_msg.c utils/utils_header.h
	$(CC) -c utils/send_read_msg.c -o $(OBJ_DIR)send_read_msg.o

clean:
	rm server client $(OBJ_DIR)*.o $(BASH_OBJ_DIR)*.o
clean_log:
	rm -rf log.txt