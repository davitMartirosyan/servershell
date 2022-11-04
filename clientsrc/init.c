#include "include/servershell.h"

t_table *create_client_table(char *ip, int port)
{
    t_table *table;

    table = malloc(sizeof(t_table));
    if(!table)
        return (NULL);

    table->type = AF_INET;
    table->proto = SOCK_STREAM;
    table->ip   =  ip;
    table->port  = port;
    table->socket_client_fd = socket(table->type, table->proto, 0);

    if(table->socket_client_fd == -1)
        table->socket_status = ERR_SOCKET_MSG;
        
    table->fields.sin_family = table->type;
    table->fields.sin_port = htons(table->port);
    if(inet_pton(table->type, table->ip, &table->fields.sin_addr) <= 0)
        table->binding_status = ERR_BINDING_MSG;

    table->connection = connect(table->socket_client_fd, \
        (struct sockaddr*)&table->fields, sizeof(table->fields));
    if(table->connection < 0)
        table->conn_status = ERR_CONN_MSG;

    return (table);
}