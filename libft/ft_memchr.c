/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:50:51 by azmakhlo          #+#    #+#             */
/*   Updated: 2024/11/13 16:41:03 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ss;
	size_t			v;

	v = 0;
	ss = (unsigned char *)s;
	while (n > v)
	{
		if (ss[v] == (unsigned char) c)
			return (ss + v);
		v++;
	}
	return (NULL);
}
