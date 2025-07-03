/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:07:04 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/06/28 13:06:52 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ma;
	size_t	i;

	i = 0;
	ma = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!ma)
		return(strerror(errno), NULL);
	while (s1[i])
	{
		ma[i] = s1[i];
		i++;
	}
	ma[i] = '\0';
	return (ma);
}
