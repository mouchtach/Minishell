/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:52:21 by ymouchta          #+#    #+#             */
/*   Updated: 2025/06/21 11:29:36 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool    start_execution(t_shell *val)
{
    //if herdoc exist
    if(!ft_herdoc(val))
        return(false);
    // tak backup for STDIN and STDOUT
    if(!init_shell_fds(val))
        return(false);
    // if have only command built in >>>
    if (is_built(val->list->cmd[0]) && !val->list->next)
    {
        if(!set_redirection(val->list))
            return(cleanup_shell_fds(val), false);
        if(!ft_dup_std(val->list))
            return(cleanup_shell_fds(val), false);
        built_in_function(val->list->cmd, val);
        reset_stdin(val);
    }
    else
        // in this condition  we have more commandes  or command not builtin
        ft_fork(val);
    // close backup files
    cleanup_shell_fds(val);
    return(true);
}
