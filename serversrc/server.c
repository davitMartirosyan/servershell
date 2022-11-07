#include "bash/includes/minishell_header.h"
#include "../utils/send_read_msg.c"

# define PORT 8080
#define EXIT_MSG "bye"

int client_fd = 0;
int server_fd = 0;

void exit_func()
{
    // closing the connected socket
    close(client_fd);
    // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);
    exit(0);
}

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

//        client_fd = table->socket_client_fd;
//        server_fd = table->socket_server_fd;
//        signal(SIGINT, exit_func);

        while(1)
        {

            read_msg(table->socket_client_fd, &table->cmdline);

            printf("Server: command output ~ %s\n", table->cmdline);

            if (!strcmp(table->cmdline, EXIT_MSG))
                break;

            table->cmd_output = "hello aper!!))";

            send_msg(table->socket_client_fd, table->cmd_output);
        }

        exit_func();

    }
    return (0);
}
