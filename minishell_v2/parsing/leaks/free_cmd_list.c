/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 10:51:25 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/06/21 17:16:14 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	free_redirections(t_redirec *red)
{
	t_redirec	*tmp;

	while (red)
	{
		tmp = red;
		p1char(&red->name);
		red = red->next;
		free(tmp);
	}
}

void	cmdfree(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		if (cmd->cmd)
			p2char(&cmd->cmd);
		if (cmd->redirec)
			free_redirections(cmd->redirec);
		cmd = cmd->next;
		free(tmp);
	}
}
