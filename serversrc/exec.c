// #include "includes/minishell_header.h"

// void send_msg(int fd, char* msg, int16_t size_msg)
// {
//     // send size of command
//     if(send(fd, &size_msg, 2, 0) < 0)
//     {
//         perror("Error, send size of command");
//         exit(EXIT_FAILURE);
//     }

//     // send command
//     if(send(fd, msg, size_msg, 0) < 0)
//     {
//         perror("Error, send command");
//         exit(EXIT_FAILURE);
//     }
// }


// int execution(table->token, char *paths[])
// {
//     char *command_name; 
//     int j = 0;

    
//     while(command_massiv[j] != '\0')
//     {
//         int i = 0;
//         while(paths[i] != '\0')
//         {

//             command_name = command_massiv[j][0];
//             if(command_name == 'exit')
//             {
//                 printf('bye bye from server');
//                 return 0;
//             }
//             char *comm = "/";
//             char *comm = strcat(comm, command_name);
//             char* command_path = ft_strjoin(paths[i],comm);

//             if(access(command_path, F_OK) ==  0)
//             {

//                 int child;
//                 child = fork();
//                 int fd = open("input.txt",O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
//                 if (child == 0)
//                 {
//                     //child                   
//                     // int fd_out = dup(1); 
//                     dup2(STDOUT,fd);
//                     execv(command_path,command_massiv[j]);
                    
//                 }
//                 else
//                 {
//                     //main 

//                     struct stat sb;
//                     if (stat(fd, &sb) == -1) 
//                     {
//                         perror("stat");
//                         exit(EXIT_FAILURE);
//                     }
//                     long long int size_ = sb.st_size;
//                     printf("%lld\n", sb.st_size);
                    
//                     char *buff = malloc(size_);
//                     read(fd, buff, size_);   
//                     if (read(fd, buff, size_) < 0) {
//                         perror("Error read command output");
//                         exit(EXIT_FAILURE);
//     }                 
//                     send_msg(fd,buff,size_);
//                 }


//             }
//             // else
//             // {
//         //it is not that necessary to have else , it will check continiusly if
//         // there were any real path , and if not it will get out of the 
//         // while? , and then i can return" there were nothing suitable

//             // }
//         }
//         printf("%s  : command not found", command_name);
//         i++;
//     }

// }

