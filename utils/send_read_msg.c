//#include "../include/servershell.h"
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>

void send_msg(int fd, char* msg, int16_t size_msg)
{
    // send size of command
    if(send(fd, &size_msg, 2, 0) < 0)
    {
        perror("Error, send size of command");
        exit(EXIT_FAILURE);
    }

    // send command
    if(send(fd, msg, size_msg, 0) < 0)
    {
        perror("Error, send command");
        exit(EXIT_FAILURE);
    }
}

void read_msg(int fd, char** msg, int16_t* size_msg)
{
    // read size of command output
    if (read(fd, size_msg, 2) < 0) {
        perror("Error, read size of command output");
        exit(EXIT_FAILURE);
    }
//    printf("read size of msg ~ %d\n", *size_msg);

    //read command output
    *msg = (char *)(malloc(*size_msg));
    if (read(fd, *msg, *size_msg) < 0) {
        perror("Error read command output");
        exit(EXIT_FAILURE);
    }
//    printf("read msg ~ %s\n", *msg);

}
