/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 21:51:33 by ymouchta          #+#    #+#             */
/*   Updated: 2025/06/21 13:38:02 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void    child_process(t_shell *val, t_cmd *cmd)
{
    char *path;

    //  set in and out  index
    if(!set_redirection(cmd))
        exit(1);
    // set pip if exist
    if(!set_pip(cmd))
        exit(1);
    // dup in and out
    if(!ft_dup_std(cmd))
         exit(1);
    // close backup we dont needed
    cleanup_shell_fds(val);
    // if fuction builtin we use my fuction
    if(is_built(cmd->cmd[0]))
    {
        if(!built_in_function(cmd->cmd, val))
            exit(1);
        exit(0);
    }
    else
    {
        path = get_path_cmd(val->path, cmd->cmd[0]);
        if(!path)
            exit(127);
        if(execve(path, cmd->cmd, NULL) == -1)
            exit(1);
    }
}

void    parent_process(t_cmd *cmd)
{
    if(cmd->fd_pip[1] > 0)
        close(cmd->fd_pip[1]);
    if(cmd->fd_herdoc[0] > 0)
        close(cmd->fd_herdoc[0] );
    if(cmd->prev)
    {
        if(cmd->prev->prev)
        {
            if(cmd->prev->prev->fd_pip[0] > 0)
                close(cmd->prev->prev->fd_pip[0]);
        }
    }
}
void    ft_fork(t_shell *val)
{
    t_cmd   *list;
    int     fork_pid;

    list = val->list;
    while(list)
    {
        // creat pipe if we have next == pipe exist
        if(list->next)
            pipe(list->fd_pip);
        fork_pid = fork();
        if(fork_pid < 0)
            perror(FORK_FAILD);
        if(fork_pid == 0)
            child_process(val, list);
        if(fork_pid > 0)
            parent_process(list);
        if(list->prev)
        {
            if (list->prev->fd_pip[0] > 0)
                close(list->prev->fd_pip[0]);
        }
        reset_stdin(val);
        list = list->next;
    }
    while(wait(NULL) > 0);
}
