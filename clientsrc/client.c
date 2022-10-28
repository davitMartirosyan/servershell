#include "../include/servershell.h"
#include "../utils/send_read_msg.c"

//#define IP "139.144.26.27"
#define IP "127.0.0.1"
#define PORT 8080
#define EXIT_MSG "bye"

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
            // reading command
            table->cmdline = readline("~ ");
            table->size_cmdline = (int16_t) strlen(table->cmdline);

            printf("Client: reading command ~ %s\nsize of reading command ~ %d\n", \
            table->cmdline, \
            table->size_cmdline\
            );

            send_msg(table->socket_client_fd, table->cmdline, table->size_cmdline);

            if (!strcmp(table->cmdline, EXIT_MSG))
                break;

            read_msg(table->socket_client_fd, &table->cmd_output, &table->size_output);

            printf("Client: command output size of ~ %hd\n", table->size_output);
            printf("Client: command output ~ %s\n", table->cmd_output);

        }

        // closing the connected socket
        close(table->socket_client_fd);
    }
}

// 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