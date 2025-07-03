/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:01:41 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/06/20 14:08:50 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*c;
	size_t	len;
	size_t	i;

	if(!str)
		return (NULL);
	len = ft_strlen(str);
	c = (char *)malloc (sizeof(char) * (len + 1));
	if (c == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		c[i] = str[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}
