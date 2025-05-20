/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:56:12 by ymouchta          #+#    #+#             */
/*   Updated: 2025/05/18 18:27:06 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool    input_redirection(t_cmd *list)
{
    t_redirec *tmp;
    
    list->fd_io[0] = STDIN_FILENO;
    tmp = list->input;
    while(tmp)
    {
        if(tmp->type == D_HERDOC)
        {
            printf("herdoc\n");
            list->fd_io[0] = open(HEREDOC_FILE, O_RDONLY, 0600);
            if(list->fd_io[0] == -1)
                return(perror(""), false);
        }
        else if(tmp->type == D_IN)
        {
            printf("input\n");
            list->fd_io[0] = open(tmp->name, O_RDONLY ,0777);
            if(list->fd_io[0] == -1)
                return(perror(""), false);
        }
        if(tmp->next)
            close(list->fd_io[0]);
        tmp = tmp->next;
    }
    return(true);
}

static bool    output_redirection(t_cmd *list)
{
    t_redirec *tmp;
    list->fd_io[1] = STDOUT_FILENO;
    tmp = list->output;
    while(tmp)
    {
        if(tmp->type == D_APPEND)
        {
            printf("apend\n");
            list->fd_io[1] = open(tmp->name, O_CREAT | O_RDWR | O_APPEND, 0777);
            if(list->fd_io[1] == -1)
                return(perror(""), false);
        }
        else if(tmp->type == D_OUT)
        {
            printf("output\n");
            list->fd_io[1] = open(tmp->name, O_CREAT | O_RDWR | O_TRUNC ,0777);
            if(list->fd_io[1] == -1)
                return(perror(""), false);
        }
        if(tmp->next)
            close(list->fd_io[1]);
        tmp = tmp->next;
    }
    return(true);
}

bool   redirection(t_cmd *list)
{
    if(!input_redirection(list))
        return(false);
    if(!output_redirection(list))
        return(false);
    if(list->next && list->fd_io[1] == STDOUT_FILENO)
    {
        printf("set_pip output for command: %s\n", list->cmd[0]);
        list->fd_io[1] = list->fd_pip[1];
    }
    else
        close(list->fd_pip[1]);

        
    if(list->prev && list->fd_io[0] == STDIN_FILENO)
    {
        printf("set_pip input for command: %s\n", list->cmd[0]);
        list->fd_io[0] = list->prev->fd_pip[0];
        // close()
    }
    else
        close(list->prev->fd_pip[0]);
    return(true);
    
}
