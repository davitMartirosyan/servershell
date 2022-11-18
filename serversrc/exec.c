
#include "bash/includes/minishell_header.h"


char* path_finder(char* command,  char* paths[])
{
    int i = 0;
    char* working_path = NULL;; //check in execution
    while(paths[i])
    {
        
        char *com = "/";
        char *comm = ft_strjoin(com, command);
        char* command_path = ft_strjoin(paths[i],comm);
        // printf("%s\n", comm);
         if(access(command_path, F_OK) ==  0)
        {
            // printf("found the path\n");
            working_path = command_path;
            return working_path;
        
        }

        i++;

    }

    return working_path;
}

void execution(Logger *l, int client_fd, t_cmdline *cmd_Line, t_table *table, char **envp)
{
    int j =0;

    while(cmd_Line->cmds->arg_pack[j])
    {
        token_replacment(cmd_Line->cmds->arg_pack[j], 3, ' ');
        j++;
    }

    char *command_name = cmd_Line->cmds->arg_pack[0]; 
    char** command_massiv = cmd_Line->cmds->arg_pack;
    
        
        char* command_path = path_finder(command_name, table->paths);
        // printf("%s\n",command_path);
        if (command_path == NULL)
        {
            // printf("%s  : command not found\n", command_name);
            char* text = "command not found\n";
            send_msg_socket(l, client_fd, text);
        }
        else
        {
            int child;
            child = fork();
            int fd = open("input.txt", O_TRUNC | O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            if(fd == -1)
            {
                perror("not opened");
                return;
            }
            if (child == 0)
            {
                //child                   
                // int fd_out = dup(1); 
                dup2(fd,1);
                execve(command_path,command_massiv, envp);
                if (close(fd) < 0)
                    perror("Close error");
                
            }

            wait(NULL);

            fd = open("input.txt", O_RDONLY);
            if (fd < 0)
                perror("Open error");    

            struct stat sb;
            if (fstat(fd, &sb) == -1) 
                perror("stat");

            // printf("%jd\n", sb.st_size);

            char *buff = malloc(sb.st_size);
            if (read(fd, buff, sb.st_size) < 0)
                perror("read error");

            // printf("buffer : %s\n", buff);
            send_msg_socket(l, client_fd, buff);

            free(buff);
            if (close(fd) < 0)
                perror("Close error");

        }

}