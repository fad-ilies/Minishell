/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:27:40 by ifadhli           #+#    #+#             */
/*   Updated: 2024/11/14 13:38:08 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*#include <stdio.h>
#include <string.h>*/
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = ft_strlen(s);
	while (s[i] != (unsigned char)c)
	{
		if (i == 0 && s[i] != c)
			return ((char *) 0);
		i--;
	}
	return ((char *) &s[i]);
}

/*int	main(void)
{
	printf("%s\n", ft_strrchr("salam", 's'));
	printf("%s\n", strrchr("salam", 's'));
}*/
