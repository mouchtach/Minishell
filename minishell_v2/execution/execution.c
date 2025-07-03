/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:52:21 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/03 18:19:48 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	execute_commands(t_shell *val)
{
	if(!process_heredocs(val))
		return(false);
	init_shell_fds(val);
	if (is_builtin(val->list->cmd[0]) && !val->list->next)
	{
		if(!handle_redirections(val->list))
			return(cleanup_shell_fds(val), false);
		if(!duplicate_standard_fds(val->list))
			return(cleanup_shell_fds(val), false);
		execute_builtin(val->list->cmd, val);
		restore_standard_input(val);
	}
	else
		execute_with_fork(val);
	cleanup_shell_fds(val);
	return(true);
}
