#include "../include/servershell.h"

t_table *create_table(t_table *table, char *ip, int port)
{
    table = malloc(sizeof(t_table));
    if(!table)
        return (NULL);

    table->type = AF_INET;
    table->ip   =  ip;
    table->proto = SOCK_STREAM;
    table->socket_fd = socket(table->type, table->proto, 0);

    if(!check(table->socket_fd))
        table->socket_status = ERR_SOCKET_MSG;
        
    table->fields.sin_family = table->type;
    inet_pton(table->type, table->ip, &table->fields.sin_addr);
    table->fields.sin_port = htons(port);

    table->connection = connect(table->socket_fd, \
        (struct sockaddr*)&table->fields, sizeof(table->fields));
    if(!table->connection)
        table->conn_status = ERR_CONN_MSG;
    return (table);
}