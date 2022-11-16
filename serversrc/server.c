#include "bash/includes/minishell_header.h"
#include "exec.c"

#define PORT 8080
#define EXIT_MSG "bye"

//int client_fd = 0;
int server_fd = 0;
Logger l;

void exit_func()
{
    log_close(&l);
    // closing the connected socket
//    close(client_fd);
    // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);
    exit(0);
}

////////////////////////////
typedef struct
{
    int fd;
    char** envp;
} args;

void* thread_f(void *arg)
{

    char *cmd_line;
    int client_fd = ((args *)arg)->fd;
    printf("Client fd  %d\n", client_fd);
    t_table* table = malloc(sizeof(t_table));
    create_shell(((args *)arg)->envp, &table);
    printf("i am in THread function\n");


    while(1)
    {
        t_cmdline *parser;

        read_msg_socket(&l, client_fd, &cmd_line);

        printf("Server: command output ~ %s\n", cmd_line);

        if (!strcmp(cmd_line, EXIT_MSG))
            break;

        //in this section we do lex analyzation and execution 
        // lexical_analyzer(cmd_line, table);
        // parser = parse_tree(table, ((args *)arg)->envp);
        // execution(parser, table);
    
        char *cmd_output = "massage arrived";

        send_msg_socket(&l, client_fd, cmd_output);

    }
    close(client_fd);
    pthread_exit(NULL);

}

int main(int ac, char **av, char **envp)
{
    Logger l1;
    log_init(&l1);
    l = l1;
    log_in_file(&l1, true);

    //creating 20 thread identifiers
    pthread_t threads[20];

    t_socket_table *table;


    struct sockaddr_in mysock;

    table = malloc(sizeof(t_socket_table));
    if(!table)
        return 0;

    table->type  = AF_INET;
    table->proto = SOCK_STREAM;
    table->port  = PORT;
    table->socket_server_fd = socket(table->type, table->proto, 0);

    if(table->socket_server_fd == -1)
        table->socket_status = ERR_SOCKET_MSG;

    mysock.sin_family = table->type;
    mysock.sin_addr.s_addr = INADDR_ANY;
    mysock.sin_port = htons(table->port);

    if(bind(table->socket_server_fd, \
        (struct sockaddr*)&(mysock), \
        sizeof(mysock)) < 0)
    {
        table->binding_status = ERR_BINDING_MSG;
        fprintf(stderr, "eh --- %s\n", strerror(errno));
    }

    if(!table)
        return (0);
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
    else
    {
        printf("success\n");


        //goes to while loop becouse it will continiusly listen
        //and then when getting some recuest it gonna check the array


        for(int i =0;i < 20 ;i++)
        {
            if(listen(table->socket_server_fd, 3) < 0)
            {
                table->listening_status = ERR_LISTENING_MSG;
            }
            else
            {
                printf("listening is good 89\n");
            }

            if(table->listening_status == ERR_LISTENING_MSG)
            {
            printf("Listening Error\n");
            exit(ERR_LISTENING_MSG);
            }

            printf("i am in for \n");
            int client_size = sizeof(mysock);
            printf("%d\n", client_size);

            table->socket_client_fd = accept(table->socket_server_fd,(struct sockaddr*)&mysock,&client_size);

            if(table->socket_client_fd < 0)
                table->new_socket_status = ERR_SOCKET_MSG;

            if(table->new_socket_status == ERR_SOCKET_MSG)
            {
            printf("Accept Error\n");
            exit(ERR_SOCKET_MSG);
            }
            //now as long as there are free threads we can use their identifiers
            //and create some connections with coresponding clients
            int rc;


            //argument is arg_list
            // int fd = table->socket_client_fd;
            // printf("%s\n", args_->envp[5]);
            args *args_;
            args_ = malloc(sizeof(args));
            args_->fd = table->socket_client_fd;
            args_->envp = envp;

            rc = pthread_create(&threads[i], NULL, thread_f, args_);
            printf("thread crete result is %d\n ", rc);
            if (rc != 0) //if thread creat works it returns 0, else it returns some num
            {
                printf("\nError:unable to create thread, \n");
                // exit(-1);
                fprintf(stderr, "%s\n", strerror(errno));
            }
            // read_msg_socket(&l1, table->socket_client_fd, &table->cmdline);

            // LOG_TRACE(&l1, "Server: command ~ %s\n", table->cmdline);

            // pthread_join(threads[i], NULL);
            // closing the connected socket
            // close(table->socket_client_fd);


            // send_msg_socket(&l1, table->socket_client_fd, table->cmd_output);
        }

    }
}
