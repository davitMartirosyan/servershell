/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspecial.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 07:35:35 by root              #+#    #+#             */
/*   Updated: 2022/11/02 21:44:17 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_isspecial(int ch)
{
    if(ch == '|'|| ch == '<' || ch == '>' || ch == '\'' || ch == '\"')
        return (1);
    return (0);
}