/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:00:23 by azmakhlo          #+#    #+#             */
/*   Updated: 2024/11/12 16:49:17 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	my_len(int n)
{
	int	len;

	len = 0;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n = -n;
		len += 1;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	shorten(char *p, int n, int si, int len)
{
	if (n < 0)
	{
		n = -n;
		p[0] = '-';
		si = 1;
	}
	while (len-- > si)
	{
		p[len] = (n % 10) + 48;
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*p;
	int		len;
	int		si;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = my_len(n);
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	si = 0;
	p[len] = '\0';
	shorten(p, n, si, len);
	return (p);
}
