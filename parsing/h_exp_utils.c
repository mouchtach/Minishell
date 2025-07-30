/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_exp_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:12:30 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/07/30 18:10:19 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*exit_stats(t_exp *exp)
{
	char	*exit_status_str;

	exit_status_str = ft_itoa(exit_s(-1));
	if (!exit_status_str)
		return (exp->result[exp->j++] = '0', exp->i += 2, NULL);
	exp->j += ft_strlen(exit_status_str);
	exp->i += 2;
	return (ft_strdup(ft_strcat(exit_status_str, "\n")));
}

void	array_free(char **c)
{
	int	i;

	if (!c)
		return ;
	i = 1;
	while (c[i])
	{
		free(c[i]);
		c[i] = NULL;
		i++;
	}
	free(c);
	c = NULL;
}

int	pre_char(const char *line, int pos)
{
	if (pos <= 0)
		return (0);
	pos--;
	while (pos > 0)
	{
		if (line[pos] == ' ')
			pos--;
		else
			break ;
	}
	if (is_redir_char(line[pos]))
		return (1);
	return (0);
}

int	is_redname(const char *s, int i)
{
	int	a;

	a = 0;
	while (s[a] && i > 0)
	{
		if (s[a] == '$')
			i--;
		a++;
	}
	if (i == 0)
		return (pre_char(s, a - 1));
	return (0);
}
