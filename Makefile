CC = gcc

OBJ_DIR = ./build/
BASH_SRC_DIR = ./serversrc/bash/*/
BASH_OBJ_DIR = $(OBJ_DIR)bash/

SERVER_INCLUDES = -I serversrc/bash/includes/
CLIENT_INCLUDES = -I clientsrc/includes/

SERVER_CFLAGS = -lpthread -lreadline -o
CLIENT_CFLAGS = -lreadline -o

BASH_SRC = $(wildcard $(BASH_SRC_DIR)*.c)
BASH_OBJ = $(patsubst %.c, $(BASH_OBJ_DIR)%.o, $(notdir $(BASH_SRC)))

all: build_dir server client

build_dir:
	mkdir $(OBJ_DIR)

server: $(OBJ_DIR)server.o $(OBJ_DIR)logger.o $(OBJ_DIR)send_read_msg.o $(BASH_OBJ)
	$(CC) $(SERVER_INCLUDES) $^ $(SERVER_CFLAGS) server
$(BASH_OBJ_DIR)%.o: $(BASH_SRC_DIR)%.c
	mkdir $(BASH_OBJ_DIR)
	$(CC) -c $< -o $@
$(OBJ_DIR)server.o: serversrc/server.c
	$(CC) -c $^ -o $@

client: $(OBJ_DIR)client.o $(OBJ_DIR)init_client.o $(OBJ_DIR)logger.o $(OBJ_DIR)send_read_msg.o
	$(CC) $(CLIENT_INCLUDES) $^ $(CLIENT_CFLAGS) client
$(OBJ_DIR)client.o: clientsrc/client.c logger/logger.h
	$(CC) -c clientsrc/client.c -o $@
$(OBJ_DIR)init_client.o: clientsrc/init_client.c
	$(CC) -c $^ -o $@

$(OBJ_DIR)logger.o: logger/logger.h logger/logger.c
	$(CC) -c logger/logger.c -o $@
$(OBJ_DIR)send_read_msg.o: utils/send_read_msg.c utils/utils_header.h
	$(CC) -c utils/send_read_msg.c -o $@

clean:
	rm -rf server client $(OBJ_DIR)
clean_log:
	rm -rf log.txt