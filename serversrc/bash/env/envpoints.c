/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpoints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:20:03 by dmartiro          #+#    #+#             */
/*   Updated: 2022/11/04 12:25:59 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

t_env *env_tokenizing(char **envp)
{
    int i;
    char **_tok;
    t_env *t;
    t_env *temp;
    
    i = -1;
    t = malloc(sizeof(t_env));
    temp = t;
    while(envp[++i])
    {
        _tok = ft_split(envp[i], '=');
        t->key = _tok[0];
        t->val = _tok[1];
        if (!envp[i + 1])
			break;
        t->next =  malloc(sizeof(t_env));
        t = t->next;
    }
   return (temp);
}

void add_paths(t_env **env, shell **table)
{
    char **abs;
    t_env *tmp;

    tmp = *env;
    while(tmp)
    {
        if(!ft_strncmp(tmp->key, "PATH", ft_strlen(tmp->key)))
        {
            (*table)->paths = ft_split(tmp->val, ':');
            return ;
        }
        tmp = tmp->next;
    }
}