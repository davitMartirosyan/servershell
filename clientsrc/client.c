#include "../include/servershell.h"
#define IP "139.144.26.27"
#define PORT 8080
int main(void)
{
    t_table *table;

    table = create_client_table(table, IP, PORT);
    if(!table)
        return (0);
    if(table->socket_status == ERR_SOCKET_MSG)
    {
        table->err = "Could not resolve descriptor";
        printf("%s\n", table->err);
        exit(ERR_SOCKET_MSG);
    }
    if(table->conn_status == ERR_CONN_MSG)
    {
        table->err = "Could not resolve connection!";
        printf("%s\n", table->err);
        exit(ERR_CONN_MSG);
    }
    else
    {
        while(1)
        {
            table->cmdline = readline("~ ");
            printf("%s | %d | %d\n", \
            table->cmdline, \
            table->socket_client_fd, \
            table->connection \
            );
            send(table->socket_client_fd, table->cmdline, sizeof(table->cmdline), 0);
        }
    }
}