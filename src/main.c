/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 01:09:56 by ifadhli           #+#    #+#             */
/*   Updated: 2025/06/09 20:29:20 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    char *input;

    input = NULL;
    while(1)
    {
        input = readline("minishell : ");
        if (!input)
            break;
        ft_cd(input);
        add_history(input);
        check_pipe(input);
    }
    rl_clear_history();
    return (0);
}