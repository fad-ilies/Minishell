/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:36:47 by ifadhli           #+#    #+#             */
/*   Updated: 2024/11/19 07:16:20 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		d;
	int		f;
	int		len;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	d = 0;
	f = ft_strlen(s1);
	while (s1[d] && ft_strchr(set, s1[d]))
		d++;
	while (f > d && ft_strchr(set, s1[f - 1]))
		f--;
	len = f - d;
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, &s1[d], (len + 1));
	return (ptr);
}
