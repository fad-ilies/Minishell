/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 22:32:09 by ifadhli           #+#    #+#             */
/*   Updated: 2025/06/15 22:32:21 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*free_list(t_env *a)
{
	t_env	*next_node;

	if (!a)
		return (NULL);
	while (a)
	{
		next_node = a->next;
		free(a->name);
		free(a->value);
		free(a);
		a = next_node;
	}
	return (NULL);
}