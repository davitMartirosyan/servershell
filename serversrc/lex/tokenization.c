/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 03:00:39 by dmartiro          #+#    #+#             */
/*   Updated: 2022/10/28 18:17:09 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"

static void add_pipe(char *cmdline, int *pos, t_tok **token);

t_tok *tokenization(char *cmdline)
{
	t_tok *tokens;
	int i;

	tokens = NULL;
	i = -1;
	while(cmdline[++i])
	{
		if(cmdline[i] && ft_iswordpart(cmdline[i]))
			add_word(cmdline, &i, &tokens);
		if(cmdline[i] && cmdline[i] == '>')
			redirection(cmdline, &i, cmdline[i], &tokens);
		if(cmdline[i] && cmdline[i] == '<')
			redirection(cmdline, &i, cmdline[i], &tokens);
		if(cmdline[i] && cmdline[i] == '|')
			add_pipe(cmdline, &i, &tokens);
	}
	return (tokens);
}

static void add_pipe(char *cmdline, int *pos, t_tok **token)
{
	
}