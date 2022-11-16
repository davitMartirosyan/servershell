#ifndef SERVERSHELL_UTILS_HEADER_H
#define SERVERSHELL_UTILS_HEADER_H

#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "../logger/logger.h"

void read_msg_socket(Logger *l, int fd, char** msg);
void send_msg_socket(Logger *l, int fd, char* msg);

#endif //SERVERSHELL_UTILS_HEADER_H
