CC = gcc
SERVER_FLAGS=-I serversrc/bash/includes/
CLIENT_FLAGS=-I clientsrc/includes/
all:
	$(CC) $(SERVER_FLAGS) serversrc/bash/*/*.c logger/*.c  serversrc/server.c serversrc/init.c -lreadline -o server
	$(CC) $(CLIENT_FLAGS) clientsrc/*.c logger/*.c  -lreadline -o client
clean:
	rm -rf *.out
