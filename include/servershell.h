#ifndef SERVERSHELL_H
#define SERVER_SHELL_H

#include <sys/socket.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

typedef struct s_data
{
    char *cmdfull;
    char **tokens;
    struct s_data *next;
} t_data;

#endif