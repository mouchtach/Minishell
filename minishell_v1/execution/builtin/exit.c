/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 11:22:52 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/21 23:30:37 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_is_numeric(char *str)
{
	int	i;

	if (!str || *str == '\0')
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **cmd, t_shell **shell)
{
	printf("exit\n");
	if (cmd && cmd[1])
	{
		if (cmd[2] && ft_is_numeric(cmd[1]))
		{
			printf("minishell: exit: too many arguments\n");
			return (1);
		}
		if (!ft_is_numeric(cmd[1]))
		{
			printf("minishell: exit: %s: numeric argument required\n", cmd[1]);
			exit(255);
		}
		else
			g_exit_status = ft_atoi(cmd[1]);
	}
	else
		g_exit_status = 0;
	cleanup_shell(shell);
	exit(g_exit_status);
}
