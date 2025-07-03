/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:12:15 by azmakhlo          #+#    #+#             */
/*   Updated: 2024/11/10 21:50:10 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	x;

	if (!s)
		return ;
	x = 0;
	if (fd >= 0)
	{
		while (s[x])
		{
			ft_putchar_fd(s[x], fd);
			x++;
		}
		ft_putchar_fd('\n', fd);
	}
}
