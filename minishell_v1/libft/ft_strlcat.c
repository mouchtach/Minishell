/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:52:07 by azmakhlo          #+#    #+#             */
/*   Updated: 2024/11/17 19:54:57 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	x;
	size_t	y;
	size_t	dest_l;
	size_t	src_l;

	src_l = ft_strlen(src);
	x = 0;
	if (dst == (NULL) && dstsize == 0 && src == NULL)
		return (0);
	if (dst == (NULL) && dstsize == 0 && src != NULL)
		return (src_l);
	dest_l = ft_strlen(dst);
	if (dest_l >= dstsize)
		return (src_l + dstsize);
	while (dst[x])
		x++;
	y = 0;
	while (src[y] && x < dstsize - 1)
	{
		dst[x] = src[y];
		x++;
		y++;
	}
	dst[x] = '\0';
	return (dest_l + src_l);
}
