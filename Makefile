CC = gcc

all:
	$(CC) serversrc/*.c -o server.out
	$(CC) clientsrc/*.c -lreadline -o client.out

clean:
	rm -rf *.out
