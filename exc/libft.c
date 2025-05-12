/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:52:48 by ymouchta          #+#    #+#             */
/*   Updated: 2025/05/12 21:20:10 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exc.h"

int	ft_strcmp(char *s1,  char *s2)
{
	int			i;
	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)s + i);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;
	size_t	stlen;

	i = 0;
	if (!s)
		return (NULL);
	stlen = ft_strlen(s);
	if (start >= stlen)
		return (ft_strdup(""));
	if (len > stlen - start)
		len = stlen - start;
	p = (char *)malloc(len + 1);
	if (!p)
		return (NULL);
	while (i < len && s[start + i])
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

static char	**freep(char **p, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(p[i]);
		i++;
	}
	free(p);
	return (NULL);
}

static size_t	countwords(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static char	**pcpy(const char *s, char **p, char c, size_t x)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	while (j < x)
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] != c && s[i])
			i++;
		p[j++] = ft_substr(s, (unsigned int)start, i - start);
		if (!p[j - 1])
			return (freep(p, j));
	}
	p[j] = NULL;
	return (p);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	size_t	count;

	if (!s)
		return (NULL);
	count = countwords(s, c);
	p = (char **)malloc(sizeof(char *) * (count + 1));
	if (!p)
		return (NULL);
	return (pcpy(s, p, c, count));
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (char *)malloc(ft_strlen(s) + 1);
	if (!p)
		return (NULL);
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}