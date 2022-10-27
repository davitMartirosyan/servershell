/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 03:09:29 by dmartiro          #+#    #+#             */
/*   Updated: 2022/10/27 18:50:54 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void create_shell(char **envp, shell **bash)
{
	*bash = malloc(sizeof(shell));
	(*bash)->env = malloc(sizeof(t_env));
    (*bash)->env = env_tokenizing(envp);
	(*bash)->reserved = ft_split(RESERVED, ' ');
	add_paths(&(*bash)->env, bash);
}