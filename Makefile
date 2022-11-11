CC = gcc

all:
	$(CC) -I serversrc/bash/includes logger/*.c serversrc/bash/*/*.c ./serversrc/init.c serversrc/server.c -o server
	$(CC) -I clientsrc/includes logger/*.c clientsrc/*.c -lreadline -o client

clean:
	rm -rf server client
