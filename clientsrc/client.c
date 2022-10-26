#include "../include/servershell.h"

//#define IP "139.144.26.27"
#define IP "127.0.0.1"
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
            // reading command
            table->cmdline = readline("~ ");
            table->size_cmdline = (int16_t) strlen(table->cmdline);

            printf("Client: reading command ~ %s\nsize of reading command ~ %d\n", \
            table->cmdline, \
            table->size_cmdline\
            );

           // send size of command
            if(send(table->socket_client_fd, &table->size_cmdline, 2, 0) < 0)
            {
                perror("Error, send size of command");
                exit(EXIT_FAILURE);
            }
            printf("Client: send size of command done !\n");

            // send command
            if(send(table->socket_client_fd, table->cmdline, table->size_cmdline, 0) < 0)
            {
                perror("Error, send command");
                exit(EXIT_FAILURE);
            }
            printf("Client: send command done !\n");


            // read size of command output
            if (read(table->socket_client_fd, &table->size_read, 2) < 0) {
                perror("Error, read size of command output");
                exit(EXIT_FAILURE);
            }
            printf("Client: command output size of ~ %hd\n", table->size_read);

            //read command output
            table->read_output = (char *)(malloc(table->size_read));
            if (read(table->socket_client_fd, table->read_output, table->size_read) < 0) {
                perror("Error read command output");
                exit(EXIT_FAILURE);
            }
            printf("Client: command output ~ %s\n", table->read_output);
        }

        // closing the connected socket
        close(table->socket_client_fd);
    }
}

// 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