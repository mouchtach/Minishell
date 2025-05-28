/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:01:41 by azmakhlo          #+#    #+#             */
/*   Updated: 2024/11/17 20:30:25 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*c;
	size_t	len;
	size_t	i;

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
