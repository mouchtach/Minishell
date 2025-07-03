/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:49:22 by macbookpro        #+#    #+#             */
/*   Updated: 2025/07/03 19:52:29 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

void	print_env_list(t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->eg == true)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

bool	execute_builtin(char **cmd, t_shell *val)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		ft_echo(cmd);
	if (ft_strcmp(cmd[0], "pwd") == 0)
		printf("%s\n", get_value(val->env, "PWD"));
	if (ft_strcmp(cmd[0], "env") == 0)
		print_env_list(val->env);
	if (ft_strcmp(cmd[0], "export") == 0)
		ft_export_variable(val, cmd);
	if (ft_strcmp(cmd[0], "cd") == 0)
		ft_cd(val->env, cmd[1]);
	if (ft_strcmp(cmd[0], "unset") == 0)
		ft_unset(val, cmd);
	if (ft_strcmp(cmd[0], "exit") == 0)
		exit(0);
	return (true);
}
