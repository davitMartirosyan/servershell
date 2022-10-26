# include "../include/servershell.h"
# define PORT 8080

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
            // read size of command output
            if (read(table->socket_client_fd, &table->size_read, 2) < 0) {
                perror("Error, read size of command output");
                exit(EXIT_FAILURE);
            }
            printf("Server: command output size of ~ %hd\n", table->size_read);

            //read command output
            table->read_output = (char *)(malloc(table->size_read));
            if (read(table->socket_client_fd, table->read_output, table->size_read) < 0) {
                perror("Error read command output");
                exit(EXIT_FAILURE);
            }
            printf("Server: command output ~ %s\n", table->read_output);


            table->cmdline = "hello aper!!))";
            table->size_cmdline = (int16_t) strlen(table->cmdline);

            // send size of command
            if(send(table->socket_client_fd, &table->size_cmdline, 2, 0) < 0)
            {
                perror("Error, send size of command");
                exit(EXIT_FAILURE);
            }
            printf("Server: send size of command done !\n");

            // send command
            if(send(table->socket_client_fd, table->cmdline, table->size_cmdline, 0) < 0)
            {
                perror("Error, send command");
                exit(EXIT_FAILURE);
            }
            printf("Server: send command done !\n");
         }

        // closing the connected socket
        close(table->socket_client_fd);
        // closing the listening socket
        shutdown(table->socket_server_fd, SHUT_RDWR);

    }
    return (0);
}
