CC = gcc

all:
	$(CC) serversrc/init.c serversrc/server.c -o server
	$(CC) clientsrc/*.c -lreadline -o client

#send_read_msg.o:
#	$(CC) -c utils/send_read_msg.c


clean:
	rm -rf server client
