/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:16:38 by azmakhlo          #+#    #+#             */
/*   Updated: 2024/11/16 10:36:09 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*sa;
	unsigned char	*sb;
	size_t			i;

	sa = (unsigned char *)s1;
	sb = (unsigned char *)s2;
	i = 0;
	while (n > i)
	{
		if ((sa[i] != sb[i]))
			return ((sa[i] - sb[i]));
		i++;
	}
	return (0);
}
