#include "../include/servershell.h"
#define IP "139.144.26.27"
#define PORT 8080
int main(void)
{
    t_table *table;

    table = create_table(table, IP, PORT);
    if(!table)
        return (0);
    if(table->socket_status == ERR_SOCKET_MSG)
    {
        table->err = "Could not resolve descriptor";
        printf("%s\n", table->err);
        exit(ERR_SOCKET_MSG);
    }
    else if(table->conn_status == ERR_CONN_MSG)
    {
        table->err = "Could not resolve connection!";
        printf("%s\n", table->err);
        exit(ERR_CONN_MSG);
    }
    else
    {
        while(1)
        {
            table->cmdline = readline("~ ");
            printf("%s\n", table->cmdline);
        }
    }
}


/* 
    t_table *table;
    t_table struct has following members:
        -int     socket_fd;
        -int     connection;
        -int     port;
        -int     type;
        -int     proto;
        -int     client_status;
        -int     socket_status;
        -int     conn_status;
        -char    *cmdline;
        -char    *ip;
        -char    *send;
        -char    *recive;
        -char    *err;
        -char    *warn;




> create_table(t_table *table, char *IP, int PORT); 
    Initializes Socket table structure
    
*/