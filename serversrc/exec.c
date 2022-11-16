#include "includes/minishell_header.h"

void find_expansion_fields(char **arguments);

void find_expansion_fields(char **arguments)
{
    int i;

    i = -1;
    while(arguments[++i] != '\0')
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


int execution(t_cmdline cmd_Line, char *paths[])
{
    find_expansion_fields(cmd_Line->cmds->arg_pack);

    char *command_name = cmd_Line->t_cmds->arg_pack[0]; 
    char** command_massiv = cmd_Line->t_cmds->arg_pack;

    
    //for not builtins
    // char ** funcs = ["echo"];
    // int j = 0;
    // while(funcs[j] != '\0')
    // {
    //     if(command_name == funcs[i])
    //     {

    //     }
    // }
        
  
    int i = 0;
    while(paths[i] != '\0')
    {

        if(command_name == 'exit')
        {
            printf('bye bye from server');
            return 0;
        }
        char *comm = "/";
        char *comm = strcat(comm, command_name);
        char* command_path = ft_strjoin(paths[i],comm);

        if(access(command_path, F_OK) ==  0)
        {

            int child;
            child = fork();
            int fd = open("input.txt",O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
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
                if (stat(fd, &sb) == -1) 
                {
                    perror("stat");
                    exit(EXIT_FAILURE);
                }
                long long int size_ = sb.st_size;
                printf("%lld\n", sb.st_size);
                
                char *buff = malloc(size_);
                read(fd, buff, size_);   

                if (read(fd, buff, size_) < 0) 
                {
                    perror("Error read command output");
                    exit(EXIT_FAILURE);
                }                 
                send_msg(fd,buff,size_);
            }


        }
        
    }
    printf("%s  : command not found", command_name);
    i++;
  

}

