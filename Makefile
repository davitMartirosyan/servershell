CC = gcc

all:
	$(CC) -I serversrc/bash/includes serversrc/bash/*/*.c ./serversrc/init.c serversrc/server.c -o server
	$(CC) -I clientsrc/includes clientsrc/*.c -lreadline -o client

clean:
	rm -rf server client
