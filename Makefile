CC = gcc
SERVER_FLAGS=-I serversrc/bash/includes/
CLIENT_FLAGS=-I clientsrc/includes/
all:
	$(CC) $(SERVER_FLAGS) utils/send_read_msg.c serversrc/bash/*/*.c logger/*.c  serversrc/server.c serversrc/init_server.c -o server
	$(CC) $(CLIENT_FLAGS) utils/send_read_msg.c clientsrc/*.c logger/*.c -lreadline -o client
clean:
	rm -rf *.out

#CC = gcc
#ODIR = build
#
#$(ODIR)/%.o: clientsrc/%.c
#	$(CC) -c $< -o $@
#
#all:
#

#all: server client
#
#server: serversrc/bash/includes server.o logger.o send_read_msg.o
#	$(CC) -I serversrc/bash/includes logger.o serversrc/bash/*/*.c server.o init_server.o send_read_msg.o -o server
#server.o: serversrc/server.c
#		$(CC) -c serversrc/server.c
#init_server.o: serversrc/init_server.c
#		$(CC) -c serversrc/init_server.c
#
#
#
#client: client.o init_client.o logger.o clientsrc/includes send_read_msg.o
#	$(CC) client.o init_client.o logger.o send_read_msg.o -lreadline -o client
#client.o: clientsrc/client.c logger/logger.h
#	$(CC) -c clientsrc/client.c
#init_client.o: clientsrc/init_client.c
#	$(CC) -c clientsrc/init_client.c
#
#
#logger.o: logger/logger.c logger/logger.h
#	$(CC) -c logger/logger.c
#send_read_msg.o: utils/send_read_msg.c utils/utils_header.h
#	$(CC) -c utils/send_read_msg.c
#
#clean:
#	rm -rf server client *.o
#clean_log:
#	rm -rf log.txt