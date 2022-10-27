/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 03:17:29 by dmartiro          #+#    #+#             */
/*   Updated: 2022/10/27 18:50:07 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"

// int execute(char *cmd, t_table **table, char **envp)
// {
//     int stdindup =  dup(STDIN);
//     int stdoutdup =  dup(STDOUT);
//     printf("%d : %d\n", stdindup, stdoutdup);

//     close(stdindup);
//     close(stdoutdup);
//     return (0);
// }