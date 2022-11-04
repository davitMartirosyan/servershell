#include "minishell_header.h"

t_table *create_server_table(int port)
{
    t_table *table;

    struct sockaddr_in mysock;

    table = malloc(sizeof(t_table));
    if(!table)
        return (NULL);
    table->type  = AF_INET;
    table->proto = SOCK_STREAM;
    table->port  = port;
    table->socket_server_fd = socket(table->type, table->proto, 0);

    if(table->socket_server_fd == -1)
        table->socket_status = ERR_SOCKET_MSG;
    
    mysock.sin_family = table->type;
    mysock.sin_addr.s_addr = INADDR_ANY;
    mysock.sin_port = htons(table->port);

    if(bind(table->socket_server_fd, \
        (struct sockaddr*)&(mysock), \
        sizeof(mysock)) < 0)
        table->binding_status = ERR_BINDING_MSG;

    if(listen(table->socket_server_fd, 3) < 0)
        table->listening_status = ERR_LISTENING_MSG;
    
    int client_size = sizeof(mysock);
    table->socket_client_fd = accept(table->socket_server_fd, \
        (struct sockaddr*)&mysock, \
        &client_size);

    if(table->socket_client_fd < 0)
         table->new_socket_status = ERR_SOCKET_MSG;
    
    return (table);
}