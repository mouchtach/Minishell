/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 22:22:28 by ymouchta          #+#    #+#             */
/*   Updated: 2025/05/13 23:48:27 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    herdoc_read(char *dlm)
{
    int fd;
    char *line;

    fd = open("/tmp/.herdoc", O_CREAT | O_TRUNC | O_RDWR , 0777);
    printf("delemater =  %s\n", dlm);
    dlm = ft_strjoin(dlm , "\n");
    while(1)
    {
        ft_putstr_fd("> ", 1);
        line  = get_next_line(STDIN_FILENO);
        printf("line  = %s\n", line);
        if(!ft_strcmp(line , dlm))
            break;
        else
            ft_putstr_fd(line, fd);
        free(line);
    }
    free(line);
    free(dlm);
}

void    fork_heredoc(char *delimiter)
{
    int fork_pid;

    fork_pid = fork();
    if(fork_pid == 0)
    {
        herdoc_read(delimiter);
        exit(0);
    }
    if(fork_pid > 0)
        waitpid(fork_pid, NULL, 0);
}

void   herdoc(t_exc *val)
{
    t_cmd *tmp;
    t_redirec *tmp_red;
    
    tmp = val->list;
    while(tmp)
    {
        tmp_red = tmp->input; 
        while(tmp_red)
        {
            printf("%s\n", tmp_red->name);
            if(tmp_red->type == D_HERDOC)
                fork_heredoc(tmp_red->name);
            tmp_red = tmp_red->next;
        }
        tmp = tmp->next;
    }
}