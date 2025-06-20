/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 22:22:28 by ymouchta          #+#    #+#             */
/*   Updated: 2025/06/20 13:07:35 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    set_std_cmd(t_cmd *cmd)
{
    cmd->fd_herdoc[0] = -1;
    cmd->fd_herdoc[1] = -1;
    cmd->fd_io[0] = -1;
    cmd->fd_io[1] = -1;
    cmd->fd_pip[0] = -1;
    cmd->fd_pip[1] = -1;
}

//not free in this fuction
bool    herdoc_read(t_cmd *tmp, char *dlm)
{
    char    *line;

    dlm = ft_strjoin(dlm , "\n");
    if(!dlm)
        return(perror(JOIN_FAILD), false);
    while(1)
    {
        ft_putstr_fd("> ", 1);
        line  = get_next_line(STDIN_FILENO);
        if(!line)
        {
            free(dlm);
            return(perror(GET_LINE), false);
        }
        if(!ft_strcmp(line , dlm))
            break;
        else
            ft_putstr_fd(line, tmp->fd_herdoc[1]);
        free(line);
    }
    free(line);
    free(dlm);
    close(tmp->fd_herdoc[0]);
    close(tmp->fd_herdoc[1]);
    return(true);
}

bool    fork_heredoc(t_cmd *tmp, char *delimiter)
{
    int fork_pid;

    fork_pid = fork();
    if(fork_pid  < 0)
        return(perror(FORK_FAILD), false);
    if(fork_pid == 0)
    {
        if(!herdoc_read(tmp, delimiter))
            exit(1);
        exit(0);
    }
    if(fork_pid > 0)
    {
        close(tmp->fd_herdoc[1]);
        waitpid(fork_pid, NULL, 0);
    }
    return(true);
}

bool   ft_herdoc(t_shell *val)
{
    // while loop for all commands if herdoce
    t_cmd *tmp;
    t_redirec *redc;

    tmp = val->list;
    while(tmp)
    {
        set_std_cmd(tmp);
        redc = tmp->redirec;
        while(redc)
        {
            if(redc->type == D_HERDOC)
            {
                // open pipe for write and clode just pip[0]
                pipe(tmp->fd_herdoc);
                if(!fork_heredoc(tmp, redc->name))
                    return(perror(HERDOC_FAILD), false);
            }
            redc = redc->next;
        }
        tmp = tmp->next;
    }
    return(true);
}