/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:42:53 by ifadhli           #+#    #+#             */
/*   Updated: 2024/11/11 20:04:39 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*pla;
	const unsigned char	*ce;

	if (dest == NULL && src == NULL)
		return (NULL);
	pla = (unsigned char *)dest;
	ce = (const unsigned char *)src;
	while (n)
	{
		*pla = *ce;
		pla++;
		ce++;
		n--;
	}
	return (dest);
}
