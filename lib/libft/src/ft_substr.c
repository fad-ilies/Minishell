/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:34:04 by ifadhli           #+#    #+#             */
/*   Updated: 2024/11/17 16:33:41 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	s_len;
	unsigned int	i;

	i = 0;
	s_len = ft_strlen((char *)s);
	if (!s)
		return (NULL);
	if (start > s_len)
		return (ft_strdup(""));
	s = s + start;
	while (s[i] && len--)
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s, i + 1);
	return (str);
}
