/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:06:07 by ifadhli           #+#    #+#             */
/*   Updated: 2025/06/22 22:01:26 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env_node(t_env **env_list, char *name, char *value)
{
	t_env	*new_node;
	t_env	*tmp;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->name = name;
	new_node->value = value;
	new_node->next = NULL;
	if (*env_list == NULL)
		*env_list = new_node;
	else
	{
		tmp = *env_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

t_env	*create_env_list(char **envp)
{
	int		i;
	int		j;
	char	*name;
	char	*value;
	t_env	*env_list;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j])
		{
			if (envp[i][j] == '=')
			{
				name = ft_substr(envp[i], 0, j);
				value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]));
				add_env_node(&env_list, name, value);
				break ;
			}
			j++;
		}
		i++;
	}
	return (env_list);
}

int	is_valid_exp(char *cmd)
{
	int	i;

	if (!cmd || !cmd[0])
		return (0);
	printf("cmd[0]: %c\n", cmd[0]);
	if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
	{
		ft_putstr_fd("minishell: export: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier2\n", STDERR_FILENO);
		return (0);
	}
	i = 1;
	while (cmd[i] && cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
		{
			ft_putstr_fd("minishell: export: ", STDERR_FILENO);
			ft_putstr_fd(cmd, STDERR_FILENO);
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

void	add_or_replace(t_env **env, char *cmd)
{
	t_env	*found;
	char	*name;
	char	*value;
	int		i;

	i = 0;
	value = NULL;
	while (cmd[i] && cmd[i] != '=')
		i++;
	name = ft_substr(cmd, 0, i);
	if (!name)
		return ;
	if (cmd[i] == '=')
		value = ft_strdup(&cmd[i + 1]);
	found = find_env_node(*env, name);
	if (found)
	{
		free(found->value);
		found->value = value;
		free(name);
		return ;
	}
	else
		add_env_node(env, name, value);
}

void	export_sorted(char **env_cpy, int len_env)
{
	int		i;
	int		sorted;
	char	*swp;

	sorted = 0;
	while (!sorted)
	{
		i = 0;
		sorted = 1;
		while (i < len_env - 1)
		{
			if (ft_strcmp(env_cpy[i], env_cpy[i + 1]) > 0)
			{
				swp = env_cpy[i + 1];
				env_cpy[i + 1] = env_cpy[i];
				env_cpy[i] = swp;
				sorted = 0;
			}
			i++;
		}
	}
}

char	**cpy_env_to_tab(t_env *env)
{
	int		i;
	int		count;
	char	**tab;
	t_env	*tmp;
	char	*tmp_egal;

	i = 0;
	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		tmp_egal = ft_strjoin(tmp->name, "=");
		tab[i] = ft_strjoin(tmp_egal, tmp->value);
		free(tmp_egal);
		i++;
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	print_export(char **env_cpy)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env_cpy[i])
	{
		ft_putstr_fd("declare -x ", 1);
		while (env_cpy[i][j] && env_cpy[i][j] != '=')
		{
			write(1, &env_cpy[i][j], 1);
			j++;
		}
		if (env_cpy[i][j] == '=')
		{
			write(1, "=", 1);
			write(1, "\"", 1);
			ft_putstr_fd(&env_cpy[i][j + 1], 1);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		i++;
		j = 0;
	}
}

int	builtin_export(t_env *env_list, char **cmd)
{
	int		i;
	int		len;
	char	**cpy_env;

	i = 1;
	len = 0;
	if (!cmd[1])
	{
		cpy_env = cpy_env_to_tab(env_list);
		while (cpy_env[len])
			len++;
		export_sorted(cpy_env, len);
		print_export(cpy_env);
		return (free_tab(cpy_env), 1);
	}
	else
	{
		if (is_valid_exp(cmd[i]))
			add_or_replace(&env_list, cmd[i]);
	}
	return (1);
}
