#ifndef SERVERSHELL_H
#define SERVER_SHELL_H

#include <sys/socket.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>
//#include "../libft/libft.h"

typedef enum s_types
{
    SUCCESS_MSG,
    WARN_SOCKET_MSG,
    WARN_CONN_MSG,
    ERR_SOCKET_MSG,
    ERR_CONN_MSG,
    ERR_BINDING_MSG,
    ERR_LISTENING_MSG
}t_types;

typedef struct s_table
{
    int     socket_client_fd;
    int     socket_server_fd;
    int     connection;
    int     port;
    int     type;
    int     proto;
    int     client_status;
    int     server_status;
    int     socket_status;
    int     new_socket_status;
    int     conn_status;
    int     binding_status;
    int     listening_status;
    char    *cmdline;
    int16_t size_cmdline;
    char    *ip;
    char    *send;
    char    *recive;
    char    *err;
    char    *warn;
    char*   read_output;
    int16_t  size_read;
    struct sockaddr_in fields;
} t_table;

t_table *create_client_table(char *ip, int port);
t_table *create_server_table(int port);

#endif