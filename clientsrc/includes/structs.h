/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:36:09 by dmartiro          #+#    #+#             */
/*   Updated: 2022/11/16 11:58:31 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H
/*  
   ' '-> ?  -> 3
    $ -> ?  -> 4
    | -> ?  -> 5
    ' -> \a -> 7
    " -> \b -> 8
*/

typedef struct s_table t_table;
typedef struct s_cmdline t_cmdline;
typedef struct s_env t_en;
typedef struct s_tok t_tok;
typedef struct s_cmds t_cmds;
typedef int (*t_built)(t_cmds *, t_table *);

typedef enum s_types_t
{
    SUCCESS_MSG,
    WARN_SOCKET_MSG,
    WARN_CONN_MSG,
    ERR_SOCKET_MSG,
    ERR_CONN_MSG,
    ERR_BINDING_MSG,
    ERR_LISTENING_MSG
}t_types_t;

typedef enum s_types
{
    STDIN,         // 0  0
    STDOUT,        // 1  1
    STDERR,        // 2  2
    SEP,           // 3  [' ']
    WORD,          // 4  [A-Z_0-9]
    SGL,           // 5  '
    DBL,           // 6  "
    EXP_FIELD,     // 7  "..." || '...'
    REDIR_OUT,     // 8  >
    REDIR_IN,      // 9  <
    APPEND,        // 10 >>
    HEREDOC,       // 11 <<
    PIPE,          // 12 |
    UNDEFINED      // 13
} t_type;


typedef struct s_cmdline
{
    t_cmds  *cmds;
    char    **env;
    pid_t   pid;
}   t_cmdline;

typedef struct s_cmds
{
    char    **arg_pack;
    char    *path;
    int     i_stream;
    int     o_stream;
    struct  s_cmds *next;
}   t_cmds;

typedef struct s_env
{
    char *key;
    char *val;
    struct s_env *next;
} t_env;

typedef struct s_tok
{
    int     len;
    char    *tok;
    int     type;
    struct  s_tok *next;
} t_tok;

typedef struct shell{
    char        **minienv;
    char        **paths;
    char        **reserved;
    int         q_c[2];
    t_built     builtin[7];
    t_env       *env;
    t_tok       *token;
} shell;

typedef struct socket_table
{
    int     socket_client_fd;
    int     socket_server_fd;
    int     connection;
    int     port;
    int     type;
    int     proto;
    int     client_status;
    int     server_status;
    int     socket_status;
    int     new_socket_status;
    int     conn_status;
    int     binding_status;
    int     listening_status;
    char    *cmdline;
    int16_t size_cmdline;
    char    *ip;
    char    *send;
    char    *recive;
    char    *err;
    char    *warn;
    char*   read_output;
    int16_t  size_read;
    
} t_table;

#endif