/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:43:15 by ifadhli           #+#    #+#             */
/*   Updated: 2025/06/16 19:55:51 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(void)
{
	char	cwd[PATH_MAX];

	// char *cwd;
	// cwd = getcwd(NULL, 0);
	getcwd(cwd, sizeof(cwd));
	// if (!cwd)
	// {
	// 	perror("pwd");
	// 	return (1);
	// }
	printf("%s\n", cwd);
	// free(cwd);
	return (0);
}

int	builtin_env(t_env *env_list)
{
	t_env	*tmp;

	tmp = env_list;
	// pointeur tmp quon initialise avec la tete de la liste
	while (tmp)
	{
		if (tmp->value)
			// si variable a une valeur,on affiche son nom et sa valur
			printf("%s=%s\n", tmp->name, tmp->value);
		else // sinon on affiche uniquement son nom
			printf("%s\n", tmp->name);
		tmp = tmp->next;
	}
	return (0);
}

int	builtin_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (args[i] && ft_strncmp(args[i], "-n", 5) == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}

void	error_cd(void)
{
	static char	*oldpwd;
	char		*cwd;

	cwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		printf("oldpwd not set");
		free(cwd);
		return ;
	}
	printf("%s\n", oldpwd);
	if (chdir(oldpwd) == -1)
	{
		perror("cd");
		free(cwd);
		return ;
	}
	free(cwd);
	return ;
}

void	ft_cd(char *path)
{
	static char	*oldpwd;
	char		*cwd;

	cwd = getcwd(NULL, 0);
	if (!path || !path[0])
	{
		path = getenv("HOME");
		if (!path)
			return (printf("HOME not set"), free(cwd), free(oldpwd));
	}
	else if (strcmp(path, "-") == 0)
		return (error_cd());
	if (chdir(path) == -1)
	{
		perror("cd");
		free(cwd);
		return ;
	}
	if (oldpwd)
		free(oldpwd);
	oldpwd = cwd;
	free(cwd);
}

t_env	*builtin_unset(t_env *env, char *cmd)
{
	t_env	*previous;
	t_env	*current;

	previous = NULL;
	current = env;
	while (current)
	{
		if (ft_strcmp(current->name, cmd) == 0)
		{
			if (previous)
				previous->next = current->next;
			else
				env = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return (0);
		}
		previous = current;
		current = current->next;
	}
	return (env);
}
