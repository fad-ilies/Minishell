/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 02:33:36 by ifadhli           #+#    #+#             */
/*   Updated: 2024/11/20 03:23:46 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

static	int	ft_countword(const char *str, char c)
{
	int	num;
	int	i;

	num = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] && str[i] != c)
		{
			while (str[i] && str[i] != c)
				i++;
			num++;
		}
		else
			i++;
	}
	return (num);
}

char	**ft_split(char const *s, char c)
{
	char		**tbl;
	size_t		wlen;
	int			i;

	tbl = (char **)malloc(sizeof(char *) * (ft_countword(s, c) + 1));
	if (!s || !tbl)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (!ft_strchr(s, c))
				wlen = ft_strlen(s);
			else
				wlen = ft_strchr(s, c) - s;
			tbl[i++] = ft_substr(s, 0, wlen);
			s += wlen;
		}
	}
	tbl[i] = 0;
	return (tbl);
}
