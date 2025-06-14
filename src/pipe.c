/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 01:02:11 by ifadhli           #+#    #+#             */
/*   Updated: 2025/05/28 20:41:28 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    check_pipe(char *input)
{
    int     i;

    i = 0;
    while (input[i] == ' ')
        i++;
    if (input[i] == '|')
    {
        ft_putendl_fd("syntax error near unexpected token `|'", STDERR_FILENO);
        return ;
    }
    i = ft_strlen(input) - 1;

    if (input[i] == '|')
        ft_putendl_fd("bash: syntax error: unexpected end of file", STDERR_FILENO);
    i = 0;
    while (input[i])
    {
        if (input[i] == '|' && input[i + 1] == '|')
            ft_putendl_fd("syntax error near unexpected token `|'", STDERR_FILENO);
        i++;            
    }
}