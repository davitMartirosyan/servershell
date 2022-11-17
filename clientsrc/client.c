#include "includes/minishell_header.h"

//#define IP "139.144.26.27"
#define IP "127.0.0.1"
#define PORT 8080
#define EXIT_MSG "bye"
#define CLIENT_MSG "Am I connected?\n"
#define INTERVAL_REQUEST 2000

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
//    log_in_file(&l1, true);

    char cl_msg[] = {CLIENT_MSG};
    char* server_msg;
    server_msg = malloc(25);

    t_socket_table *table;

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

            ///////////////////////////////////PING/////////////////////////////////////////////
            
            // clock_t interval,init_send;
            // int timer_ms = 0;
            //timer_ms = IntervalTimer(&interval,&init_send);
            time_t t1;
            time(&t1);
            // printf("Timer starts\n");
            // take_enter();
            // printf("Timer ends\n");
            time_t t2;
            time(&t2);
            double t = t2 - t1;
            double time_taken = ((double)t); // calculate the elapsed time
            //printf("The program took %f seconds to execute", time_taken);
            // struct hostent* resolv;
            // resolv = gethostbyname(IP);
            if(time_taken <= INTERVAL_REQUEST)
            {
                int send_m = send(table->socket_client_fd, cl_msg, strlen(cl_msg), 0);
                if (send_m < 0)
                printf("Lilia send error!!\n");
            }


            
           
            //printf("Lilia send done\n");
            
            recv(table->socket_client_fd, server_msg, 25, 0);
            if(!strcmp(server_msg, "Yes. You're connected\n")){
                time_t t;
                time(&t);
                printf(" YOU ARE CONNECTED, Exact time is: %s\n", ctime(&t));
            }
            else{
                printf("YOU LOST CONNECTION\n");
            }
            //read_msg(table->socket_client_fd, &server_msg);
            // int recv_m = recv(table->socket_client_fd, server_msg, 25, 0);
            // if(recv_m < 0){
            //     printf("Can't receive msg from server(Lilia)");
            // }
            // else{
            //     printf("Recieved msg from server(Lilia)");
            // }
///////////////////////////////////////////////////////////////////////////////

            // reading command
            table->cmdline = readline("~ ");

            LOG_TRACE(&l1, "Client: reading command ~ %s\n", table->cmdline);

            send_msg_socket(&l1, table->socket_client_fd, table->cmdline);

            if (!strcmp(table->cmdline, EXIT_MSG))
                break;

            read_msg_socket(&l1,table->socket_client_fd, &table->cmd_output);

            LOG_TRACE(&l1, "Client: command output ~ %s\n", table->cmd_output);

        }

        // closing the connected socket
        exit_func();
    }
}

// gcc -I includes/ *.c -lreadline -o client && ./client