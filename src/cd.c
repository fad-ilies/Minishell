/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:36:07 by ifadhli           #+#    #+#             */
/*   Updated: 2025/06/10 19:19:03 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char *ft_get_env(char *name, t_env *env)
// {
//     t_env   *current;
    
//     current = env;
//     while(current)
//     {
//         if (ft_strcmp(name, current->key) == 0)
//             return (current->valeur);
//         current = current->next;
//     }
//     return (NULL);
// }

// void    ft_set_env(char *name, char *new_val, t_env *env)
// {
//     t_env       *current;
    
//     current = env;
//     while (current)
//     {
//         if (ft_strcmp(name, current->key) == 0)
//         {
//             free(current->valeur);
//             if (!new_val)
//             {
//                 current->valeur = NULL;
//                 return ;
//             }
//             current->valeur = ft_strdup(new_val);
//             return ;
//         }
//         else
//         {
            
//         }
//     }
// }
// int	built_cd_v2(char *cmd)
// {
// 	char *oldpwd;
    
// 	oldpwd = ft_get_env("PWD", );
// 	if (cmd == NULL || ft_strcmp(cmd, "~") == 0)
// 	{
// 		cmd = ft_get_env("HOME");
// 		if (!cmd)
// 		{
// 			printf("syntax error : HOME not set\n");
// 			return (1);
// 		}
// 	}
// 	else if (ft_strcmp(cmd, "-") == 0)
// 	{
// 		cmd = ft_get_env("OLDPWD");
//         if (!cmd)
//         {
//             printf("syntax error : OLDPWD not set\n");
// 			return (1);
//         }
// 	}
//     if (chdir(cmd) == -1)
//         return(perror("cd"), 1);
//     return (0);
// }


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
			return(printf("HOME not set"), free(cwd));
	}
	else if (strcmp(path, "-") == 0)
		error_cd();
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
