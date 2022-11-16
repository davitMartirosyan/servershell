#CC = gcc
#SERVER_FLAGS=-I serversrc/bash/includes/
#CLIENT_FLAGS=-I clientsrc/includes/
#all:
#	$(CC) $(SERVER_FLAGS) utils/send_read_msg.c serversrc/bash/*/*.c logger/*.c  serversrc/server.c -lpthread -lreadline -o server
#	$(CC) $(CLIENT_FLAGS) utils/send_read_msg.c clientsrc/*.c logger/*.c -lreadline -o client
#clean:
#	rm -rf *.out

#ODIR = build
#
#$(ODIR)/%.o: serversrc/bash/%.c
#	$(CC) -c $< -o $@

CC = gcc
SERVER_FLAGS=-I serversrc/bash/includes/
CLIENT_FLAGS=-I clientsrc/includes/

all: server client

server: server.o logger.o send_read_msg.o
	$(CC) $(SERVER_FLAGS) serversrc/bash/*/*.c logger.o server.o send_read_msg.o -lpthread -lreadline -o server
server.o: serversrc/server.c
		$(CC) -c serversrc/server.c


client: client.o init_client.o logger.o send_read_msg.o
	$(CC) $(CLIENT_FLAGS) client.o init_client.o logger.o send_read_msg.o -lreadline -o client
client.o: clientsrc/client.c logger/logger.h
	$(CC) -c clientsrc/client.c
init_client.o: clientsrc/init_client.c
	$(CC) -c clientsrc/init_client.c


logger.o: logger/logger.c logger/logger.h
	$(CC) -c logger/logger.c
send_read_msg.o: utils/send_read_msg.c utils/utils_header.h
	$(CC) -c utils/send_read_msg.c

clean:
	rm -rf server client *.o
clean_log:
	rm -rf log.txt