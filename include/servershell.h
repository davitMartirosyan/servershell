#ifndef SERVERSHELL_H
#define SERVER_SHELL_H

#include <sys/socket.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

typedef enum s_types
{
    SUCCESS_MSG,
    WARN_SOCKET_MSG,
    WARN_CONN_MSG,
    ERR_SOCKET_MSG,
    ERR_CONN_MSG,
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
    int     socket_status;
    int     conn_status;
    char    *cmdline;
    char    *ip;
    char    *send;
    char    *recive;
    char    *err;
    char    *warn;
    struct sockaddr_in fields;
} t_table;

int check(int rtrn);

t_table *create_client_table(t_table *table, char *ip, int port);
t_table *create_server_table(t_table *table, char *ip, int port);

#endif