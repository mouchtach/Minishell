/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 11:22:52 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/31 16:13:54 by ymouchta         ###   ########.fr       */
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
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		if (!ft_is_numeric(cmd[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd("numeric argument required\n", 2);
			exit(255);
		}
		else
			exit_s(ft_atoi(cmd[1]));
	}
	else
		exit_s(0);
	cleanup_shell(shell);
	exit(exit_s(-1));
}
