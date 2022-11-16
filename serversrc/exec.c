#include "minishell_header.h"



void send_msg_server(int fd, char* msg)
{
    int16_t size_msg = (int16_t) strlen(msg);

    // send size of command
    if(send(fd, &size_msg, 2, 0) < 0)
    {
        perror("Error, send size of command");
        exit(EXIT_FAILURE);
    }
//    printf("Send msg size done!\n");

    // send command
    if(send(fd, msg, size_msg, 0) < 0)
    {
        perror("Error, send command");
        exit(EXIT_FAILURE);
    }
//    printf("Send msg done!\n");
}

void find_expansion_fields(char **arguments);

void find_expansion_fields(char **arguments)
{
    int i;

    i = -1;
    while(arguments[++i])
    {
        token_replacment(arguments[i], 3, ' ');
    }
}

/*
t_cmdline this is the main struct 
it contains *t_cmds
which contains the **arg pack , in which is the inputed command line 
getting which is like as follows
t_cmdline cmd_line;
cmd = cmd_Line->t_cmds->arg_pack[0]
args = from 1 to end
function exectuin gets the instance of struct t_cmdline and paths of builtins


*/


int execution(t_cmdline *cmd_Line, t_table *table)
{
    find_expansion_fields(cmd_Line->cmds->arg_pack);

    char *command_name = cmd_Line->cmds->arg_pack[0]; 
    printf(" command is %s\n", command_name);
    char** command_massiv = cmd_Line->cmds->arg_pack;
    printf(" command 1st arg is %s\n", command_massiv[1]);
    int i = 0;
    while(table->paths[i])
    {
        printf("i am in exec's while 41 line \n");
        if(command_name == "exit")
        {
            printf("bye bye from server");
            return 0;
        }
        char *comm = "/";
        comm = strcat(comm, command_name);
        char* command_path = ft_strjoin(table->paths[i],comm);
        printf("%s\n", comm);
        if(access(command_path, F_OK) ==  0)
        {

            int child;
            child = fork();
            int fd = open("input.txt", O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            if (child == 0)
            {
                //child                   
                // int fd_out = dup(1); 
                dup2(STDOUT,fd);
                execv(command_path,command_massiv);
                
            }
            else
            {
                //main 

                struct stat sb;
                if (fstat(fd, &sb) == -1) 
                {
                    perror("stat");
                    exit(EXIT_FAILURE);
                }
                long long int size_ = sb.st_size;
                printf("%ld\n", sb.st_size);
                
                char *buff = malloc(size_);
                read(fd, buff, size_);   

                if (read(fd, buff, size_) < 0) 
                {
                    perror("Error read command output");
                    exit(EXIT_FAILURE);
                }                 
                send_msg_server(fd,buff);
                free(buff);
            }


        }
        
    }
    printf("%s  : command not found", command_name);
    i++;
  

}

