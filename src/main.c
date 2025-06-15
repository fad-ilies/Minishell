/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 01:09:56 by ifadhli           #+#    #+#             */
/*   Updated: 2025/06/15 22:32:31 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	**args;
	t_env	*env_list;

	(void)ac;
	(void)av;
	input = NULL;
	args = NULL;
	env_list = create_env_list(envp);
	// builtin_env(env_list);
	while (1)
	{
		input = readline("minishell : ");
		if (!input)
			break ;
		add_history(input);
		args = ft_split(input, ' ');
		if (!args || !args[0])
		{
			free(input);
			free_tab(args);
			continue ;
		}
		if (are_double_quotes_closed(input) != 0
			|| are_single_quotes_closed(input) != 0)
		{
			free(input);
			free_tab(args);
			return (1);
		}
		neutralize_special_char_in_double_quote(input);
		neutralize_special_char_in_single_quote(input);
		exec_builtin(args, env_list);
		syntax_special_char(input);
		free(input);
		free_tab(args);
	}
	rl_clear_history();
	free_list(env_list);
}
	