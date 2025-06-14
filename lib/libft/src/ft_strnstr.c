/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:08:54 by ifadhli           #+#    #+#             */
/*   Updated: 2024/11/14 18:29:39 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		j;

	if (ft_strlen(s2) < 1)
		return ((char *) s1);
	i = 0;
	while (s1[i] && i < n)
	{
		j = 0;
		while (s2[j] == s1[i + j] && i + j < n)
		{
			if (s1[i + j] == s2[j])
			{
				if (s2[j + 1] == '\0')
					return ((char *) &s1[i]);
			}
			else
				break ;
			j++;
		}
		i++;
	}
	return (0);
}
