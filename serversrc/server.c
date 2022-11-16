#include "bash/includes/minishell_header.h"
//#include "../logger/logger.h"
//#include "../utils/send_read_msg.c"

#define PORT 8080
#define EXIT_MSG "bye"

int client_fd = 0;
int server_fd = 0;
Logger l;

void exit_func()
{
    log_close(&l);
    // closing the connected socket
    close(client_fd);
    // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);
    exit(0);
}

//void thread_f(int *fd_s)
//{
//
//    read_msg(fd_s, &table->cmdline, &table->size_cmdline);
//
//    printf("Server: command output size of ~ %hd\n", table->size_cmdline);
//    printf("Server: command output ~ %s\n", table->cmdline);
//
//    if (!strcmp(table->cmdline, EXIT_MSG))
//        break;
//
//    //////////////////////////////in this section we do lex analyzation and execution
//    lexical_analyzer(table->cmdline, bash);
//    // execution(table->token, *paths[]); //paths harcnel Davoic vortex a pahel, u poxel tokeni pahy henc funkciayum
//
//    table->read_output = "massage arrived ^ !!))";
//    table->size_cmdline = (int16_t) strlen(table->read_output);
//
//    send_msg(table->socket_client_fd, table->read_output, table->size_cmdline);
//
//}

int main(int ac, char **av, char **envp)
{
    Logger l1;
    log_init(&l1);
    l = l1;
    log_in_file(&l1, true);

    t_table *table;
    shell   *bash;
    char    *cmdline;
    struct sockaddr_in client_addr;

    create_shell(envp, &bash);

    // printf("%s\n", arr[0][0]);

    table = create_server_table(PORT);
    if(!table)
        return 0;
    if(table->socket_status == ERR_SOCKET_MSG)
    {
        LOG_ERROR(&l1, "Could not resolve descriptor ~ %d\n", table->socket_status);
        exit(ERR_SOCKET_MSG);
    }
    if(table->binding_status == ERR_BINDING_MSG)
    {
        LOG_ERROR(&l1, "Binding Error ~ %d\n", table->binding_status);
        exit(ERR_BINDING_MSG);
    }
    if(table->listening_status == ERR_LISTENING_MSG)
    {
        LOG_ERROR(&l1, "Listening Error ~ %d\n", table->listening_status);
        exit(ERR_LISTENING_MSG);
    }
    if(table->new_socket_status == ERR_SOCKET_MSG)
    {
        LOG_ERROR(&l1, "Accept Error ~ %d\n", table->new_socket_status);
        exit(ERR_SOCKET_MSG);
    }
    else
    {
        LOG_TRACE(&l1, "%s", "success\n");

//        client_fd = table->socket_client_fd;
//        server_fd = table->socket_server_fd;
//        signal(SIGINT, exit_func);

        while (1) {

//            int rc;
//            pthread_t *thread;
//            int *fd_s = table->socket_client_fd;
//            rc = pthread_create(&thread, NULL, thread_f, &fd_s);
//
//            if (rc)
//            {
//                printf("Error:unable to create thread,");
//                exit(-1);
//            }

            read_msg_socket(&l1, table->socket_client_fd, &table->cmdline);

            LOG_TRACE(&l1, "Server: command ~ %s\n", table->cmdline);

            if (!strcmp(table->cmdline, EXIT_MSG))
                break;

            table->cmd_output = "hello aper!!))";

            send_msg_socket(&l1, table->socket_client_fd, table->cmd_output);
        }

        exit_func();
    }
}
