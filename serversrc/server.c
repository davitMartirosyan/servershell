# include "../include/servershell.h"
#include "../utils/send_read_msg.c"

# define PORT 8080
#define EXIT_MSG "bye"

int main(void)
{
    t_table *table;

    table = create_server_table(PORT);
    if(!table)
        return (0);
    if(table->socket_status == ERR_SOCKET_MSG)
    {
        printf("Could not resolve descriptor\n");
        exit(ERR_SOCKET_MSG);
    }
    if(table->binding_status == ERR_BINDING_MSG)
    {
        printf("Binding Error\n");
        exit(ERR_BINDING_MSG);
    }
    if(table->listening_status == ERR_LISTENING_MSG)
    {
        printf("Listening Error\n");
        exit(ERR_LISTENING_MSG);
    }
    if(table->new_socket_status == ERR_SOCKET_MSG)
    {
        printf("Accept Error\n");
        exit(ERR_SOCKET_MSG);
    }
    else
    {
        printf("success\n");

         while(1)
         {
            read_msg(table->socket_client_fd, &table->cmdline, &table->size_cmdline);

            printf("Server: command output size of ~ %hd\n", table->size_cmdline);
            printf("Server: command output ~ %s\n", table->cmdline);

             if (!strcmp(table->cmdline, EXIT_MSG))
                 break;

            table->cmd_output = "hello aper!!))";
            table->size_output = (int16_t) strlen(table->cmd_output);

            send_msg(table->socket_client_fd, table->cmd_output, table->size_output);
         }

        // closing the connected socket
        close(table->socket_client_fd);
        // closing the listening socket
        shutdown(table->socket_server_fd, SHUT_RDWR);

    }
    return (0);
}
