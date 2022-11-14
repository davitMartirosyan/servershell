#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "../logger/logger.h"

void send_msg(Logger *l, int fd, char* msg)
{
    int16_t size_msg = (int16_t) strlen(msg);

    // send size of command
    if(send(fd, &size_msg, 2, 0) < 0)
    {
        LOG_ERROR(l, "Error, send size of command: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    LOG_TRACE(l, "Send msg size done! ~ %d\n", size_msg);

    // send command
    if(send(fd, msg, size_msg, 0) < 0)
    {
        LOG_ERROR(l, "Error, send command: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    LOG_TRACE(l, "Send msg done! ~ %s\n", msg);
}

void read_msg(Logger *l, int fd, char** msg)
{
    int16_t size_msg = 0;

    // read size of command output
    if (recv(fd, &size_msg, 2, 0) < 0) {
        LOG_ERROR(l, "Error, read size of command output: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    LOG_TRACE(l, "read size of msg ~ %d\n", size_msg);

    //read command output
    *msg = (char *)(malloc(size_msg));
    if (recv(fd, *msg, size_msg, 0) < 0) {
        LOG_ERROR(l, "Error read command output: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    LOG_TRACE(l, "read msg ~ %s\n", *msg);

}