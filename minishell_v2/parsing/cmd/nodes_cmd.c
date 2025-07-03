/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:28:15 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/06/21 15:54:40 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_redirec	*red_node(void)
{
	t_redirec	*red;

	red = malloc(sizeof(t_redirec));
	if (!red)
		return (NULL);
	red->next = NULL;
	return (red);
}

t_cmd	*cmd_node(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->redirec = NULL;
	cmd->prev = NULL;
	cmd->next = NULL;
	return (cmd);
}
