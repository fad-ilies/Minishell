/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:43:15 by ifadhli           #+#    #+#             */
/*   Updated: 2025/06/14 19:05:03 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

int	build_echo(char **arg)
{
	int	i;
	int	nline;

	i = 0;
	nline = 0;
	if (arg[i] && ft_strncmp(arg[i], "-n", 3) == 0)
	{
		printf("%s", arg[i]);
		i++;
	}
	while (arg[i])
	{
		printf("%s", arg[i]);
		i++;
	}
	if (nline)
		printf("\n");
	return (0);
}

int	build_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

int	simple_quote(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			count++;
		i++;
	}
	if (count % 2 != 0)
	{
		printf("syntax error: unclosed single quote");
		return (1);
	}
	else
		return (0);
}
int	double_quote(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '"')
			count++;
		i++;
	}
	if (count % 2 != 0)
	{
		printf("syntax error: unclosed double quote");
		return (1);
	}
	else
		return (0);
}

int	built_cd(char *cmd)
{
	if (cmd == NULL)
	{
		cmd = getenv("HOME");
		if (!cmd)
		{
			printf("syntax error : Home not set");
			return (1);
		}
	}
	if (chdir(cmd) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	is_valid_exp(char *cmd)
{
	int	i;

	if (!cmd || !cmd[0])
		return (0);
	if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
	{
		ft_putstr_fd("minishell: export: ", STDERR_FILENO);
		ft_putstr_fd(cmd[0], STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (0);
	}
	i = 1;
	while (cmd[i] && cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
		{
			ft_putstr_fd("minishell: export: ", STDERR_FILENO);
			ft_putstr_fd(cmd[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return (0);
		}
		i++;
	}
	return (1);
}

t_env	*find_env_node(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}
