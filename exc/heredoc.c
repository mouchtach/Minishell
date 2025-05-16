/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 22:22:28 by ymouchta          #+#    #+#             */
/*   Updated: 2025/05/15 15:39:35 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool    herdoc_read(char *dlm)
{
    int fd;
    char *line;

    fd = open(HEREDOC_FILE , O_CREAT | O_TRUNC | O_RDWR , 0600);
    if(fd == -1)
        return(perror(""), false);
    dlm = ft_strjoin(dlm , "\n");
    if(!dlm)
        return(perror(""), false);
    while(1)
    {
        ft_putstr_fd("> ", 1);
        line  = get_next_line(STDIN_FILENO);
        if(!line)
            return(perror(""), false);
        if(!ft_strcmp(line , dlm))
            break;
        else
            ft_putstr_fd(line, fd);
        free(line);
    }
    free(line);
    free(dlm);
    close(fd);
    return(true);
}

bool    fork_heredoc(char *delimiter)
{
    int fork_pid;

    fork_pid = fork();
    if(fork_pid  < 0)
        return(perror(""), false);
    if(fork_pid == 0)
    {
        if(!herdoc_read(delimiter))
            exit(1);
        exit(0);
    }
    if(fork_pid > 0)
        waitpid(fork_pid, NULL, 0);
    return(true);
}

bool   ft_herdoc(t_exc *val)
{
    t_cmd *tmp;
    t_redirec *tmp_red;

    tmp = val->list;
    while(tmp)
    {
        tmp_red = tmp->input;
        while(tmp_red)
        {
            if(tmp_red->type == D_HERDOC)
                if(!fork_heredoc(tmp_red->name))
                    return(perror(""), false);
            tmp_red = tmp_red->next;
        }
        tmp = tmp->next;
    }
    return(true);
}