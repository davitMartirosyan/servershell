#include "include/servershell.h"
#include "../utils/send_read_msg.c"

//#define IP "139.144.26.27"
#define IP "127.0.0.1"
#define PORT 8080
#define EXIT_MSG "bye"
int client_fd = 0;

void exit_func()
{
    close(client_fd);
    exit(0);
}

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
        client_fd = table->socket_client_fd;
        signal(SIGINT, exit_func);

        while(1)
        {
            // reading command
            table->cmdline = readline("~ ");

            printf("Client: reading command ~ %s\n", \
            table->cmdline \
            );

            send_msg(table->socket_client_fd, table->cmdline);

            if (!strcmp(table->cmdline, EXIT_MSG))
                break;

            read_msg(table->socket_client_fd, &table->cmd_output);

            printf("Client: command output ~ %s\n", table->cmd_output);

        }

        // closing the connected socket
        exit_func();
    }
}