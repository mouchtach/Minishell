/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:52:46 by azmakhlo          #+#    #+#             */
/*   Updated: 2024/11/07 18:43:39 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*s;
	unsigned char	*d;

	if (dst == src)
		return (dst);
	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	if (d > s)
	{
		while (len-- > 0)
			d[len] = s[len];
	}
	else 
		ft_memcpy(d, s, len);
	return (dst);
}
