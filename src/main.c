/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 01:09:56 by ifadhli           #+#    #+#             */
/*   Updated: 2025/07/14 16:24:20 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(int ac, char **av, char **envp)
// {
// 	char	*input;
// 	char	**args;
// 	t_env	*env_list;

// 	(void)ac;
// 	(void)av;
// 	input = NULL;
// 	args = NULL;
// 	env_list = create_env_list(envp);
// 	// builtin_env(env_list);
// 	while (1)
// 	{
// 		input = readline("minishell : ");
// 		if (!input)
// 			break ;
// 		add_history(input);
// 		args = ft_split(input, ' ');
// 		if (!args || !args[0])
// 		{
// 			free(input);
// 			free_tab(args);
// 			continue ;
// 		}
// 		if (are_double_quotes_closed(input) != 0
// 			|| are_single_quotes_closed(input) != 0)
// 		{
// 			free(input);
// 			free_tab(args);
// 			return (1);
// 		}
// 		neutralize_special_char_in_double_quote(input);
// 		neutralize_special_char_in_single_quote(input);
// 		exec_builtin(args, env_list);
// 		syntax_special_char(input);
// 		free(input);
// 		free_tab(args);
// 	}
// 	rl_clear_history();
// 	free_list(env_list);
// }
int	g_exit_status = 0;

void	check_signal(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

//here_doc sighandler pour sigint fermer le heredoc free tout et couper toutes les commandes, redonner le prompt a l'utilisateur
//void heredoc_signal(int sig)

int	main(int ac, char **av, char **envp)
{
	char	*input;
	// char	*expanded;
	char	**args;
	t_env	*env_list;

	(void)ac;
	(void)av;
	input = NULL;
	args = NULL;
	env_list = create_env_list(envp);
	while (1)
	{
		signal(SIGINT, check_signal);
		signal(SIGQUIT, SIG_IGN);
		//signal(SIGINT, SIG_DFL); // remettre pour les signaux leur routine par defaut (fermer le programme) et cela apres le fork() 
		//signal(SIGQUIT, SIG_DFL); // remettre pour les signaux leur routine par defaut (fermer le programme)
		input = readline("minishell : ");
		if (!input)
			break ;
		add_history(input);
		if (is_quote_closed(input)!= 0)
		{
			free(input);
			continue ;
		}
		// expanded = expand_variables(input, env_list, g_exit_status);
		// free(input);
		// input = expanded;
		neutralize_special_char_in_double_quote(input);
		neutralize_special_char_in_single_quote(input);
		printf("minishell : %s\n", input);
		args = ft_split(input, ' ');
		if (!args || !args[0])
		{
			free(input);
			free_tab(args);
			continue ;
		}
		exec_builtin(args, env_list, input);
		syntax_special_char(input);
		free(input);
		free_tab(args);
	}
	rl_clear_history();
	free_list(env_list);
	return (0);
}