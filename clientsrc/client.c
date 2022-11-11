#include "includes/minishell_header.h"
#include "../utils/send_read_msg.c"
#include "../logger/logger.h"

//#define IP "139.144.26.27"
#define IP "127.0.0.1"
#define PORT 8080
#define EXIT_MSG "bye"

int client_fd = 0;
Logger l;

void exit_func() {
    log_close(&l);
    close(client_fd);
    exit(0);
}

int main(void) {
    Logger l1;
    log_init(&l1);
    l = l1;
    log_in_file(&l1, true);

    t_table *table;

    table = create_client_table(IP, PORT);
    if (!table)
        return (0);
    if (table->socket_status == ERR_SOCKET_MSG) {
        LOG_ERROR(&l1, "Could not resolve descriptor ~ %d\n", table->socket_status);
        exit(ERR_SOCKET_MSG);
    }
    if (table->conn_status == ERR_CONN_MSG) {
        LOG_ERROR(&l1, "Could not resolve connection! ~ %d\n", table->conn_status);
        exit(ERR_CONN_MSG);
    }
    if (table->binding_status == ERR_BINDING_MSG) {
        LOG_ERROR(&l1, "Invalid address: {%s} not supported\n", table->ip);
        exit(ERR_BINDING_MSG);
    } else {
        client_fd = table->socket_client_fd;
        signal(SIGINT, exit_func);

        while (1) {
            // reading command
            table->cmdline = readline("~ ");

            LOG_TRACE(&l1, "Client: reading command ~ %s\n", table->cmdline);

            send_msg(table->socket_client_fd, table->cmdline);

            if (!strcmp(table->cmdline, EXIT_MSG))
                break;

            read_msg(table->socket_client_fd, &table->cmd_output);

            LOG_TRACE(&l1, "Client: command output ~ %s\n", table->cmd_output);

        }

        // closing the connected socket
        exit_func();
    }
}

// gcc -I includes/ *.c -lreadline -o client && ./client