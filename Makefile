CC = gcc

all:
	$(CC) -I serversrc/bash/includes/ serversrc/*.c serversrc/bash/*/*.c -lreadline -o server.out
	# $(CC) -I clientsrc/includes/ clientsrc/*.c -lreadline -o client.out

clean:
	rm -rf *.out
