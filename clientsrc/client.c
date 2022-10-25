#include "../include/servershell.h"

#define IP "139.144.26.27"
#define PORT 8080

int main(void)
{
    t_table *table;

    table = create_client_table(IP, PORT);
    if(!table)
        return (0);
    if(table->socket_status == ERR_SOCKET_MSG)
    {
        printf("Could not resolve descriptor\n");
        exit(ERR_SOCKET_MSG);
    }
    if(table->conn_status == ERR_CONN_MSG)
    {
        printf("Could not resolve connection!\n");
        exit(ERR_CONN_MSG);
    }
    if(table->binding_status == ERR_BINDING_MSG)
    {
        printf("Invalid address: {%s} not supported\n", table->ip);
        exit(ERR_BINDING_MSG);
    }
    else
    {
        while(1)
        {
            //reading command
            table->cmdline = readline("~ ");
            printf("%s | %d | %d\n", \
            table->cmdline, \
            table->socket_client_fd, \
            table->connection \
            );

           //
            send(table->socket_client_fd, (char*)sizeof(table->cmdline), 2, 0);
            send(table->socket_client_fd, table->cmdline, sizeof(table->cmdline), 0);
        }
    }
}

// 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