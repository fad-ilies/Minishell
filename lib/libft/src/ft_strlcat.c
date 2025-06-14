/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:12:57 by ifadhli           #+#    #+#             */
/*   Updated: 2024/11/13 19:31:32 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t s)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (dest[i] != '\0' && i < s)
		i++;
	while (src[j] != '\0' && (i + j + 1) < s)
	{
		dest[i + j] = src[j];
		j++;
	}
	if (i < s)
		dest[i + j] = '\0';
	return (i + ft_strlen(src));
}
