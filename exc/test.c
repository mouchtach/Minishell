/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:20:39 by ymouchta          #+#    #+#             */
/*   Updated: 2025/05/19 01:53:38 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



bool    set_input(t_cmd *command, t_redirec *in)
{
    if(command->fd_io[0] != STDIN_FILENO)
        close(command->fd_io[0]);
    if(in->type == D_IN)
    {
        command->fd_io[0] = open(in->name , O_RDONLY , 0777);
        if(!command->fd_io[0])
            return(perror(""), false);
    }
    else
    {
        command->fd_io[0] = open(HEREDOC_FILE, O_RDONLY , 0777);
        if(!command->fd_io[0])
            return(perror(""), false);
    }
    return (true);
}

bool    set_output(t_cmd *command, t_redirec *out)
{
    if(command->fd_io[1] != STDOUT_FILENO)
        close(command->fd_io[1]);
    if(out->type == D_OUT)
    {
        command->fd_io[1] = open(out->name , O_CREAT | O_TRUNC | O_RDWR , 0777);
        if(!command->fd_io[1])
            return(perror(""), false);
    }
    else
    {
        command->fd_io[1] = open(out->name, O_CREAT | O_APPEND | O_RDWR , 0777);
        if(!command->fd_io[1])
            return(perror(""), false);
    }
    return (true);
}

bool    set_redirection(t_cmd *command)
{
    command->fd_io[0] = STDIN_FILENO; 
    command->fd_io[1] = STDOUT_FILENO;
    
    t_redirec *tmp;
    tmp = command->redc;
    while(tmp)
    {
        if(tmp->type == D_IN || tmp->type == D_HERDOC)
            if(!set_input(command, tmp))
                return(false);
        if(tmp->type == D_OUT || tmp->type == D_APPEND)
            if(!set_output(command, tmp))
                return(false);
        tmp = tmp->next;
    }
}
bool    set_pip(t_cmd *command)
{
    if(command->fd_io[1] != STDOUT_FILENO && command->fd_pip[1] != 0)
        close(command->fd_pip[1]);
    else if(command->fd_io[1] == STDOUT_FILENO)
        command->fd_io[1] = command->fd_pip[1];
        
    if(command->prev && command->fd_io[0] == STDIN_FILENO)
        command->fd_io[0] = command->prev->fd_pip[0];
    if(command->fd_pip[0] != 0)
        close(command->fd_pip[0]);
        
}

bool    child_process(t_exc *val, t_cmd *cmd)
{
    
}
bool    parent_process(t_cmd *cmd)
{
    
}
bool    start_execution(t_exc *val)
{
    

    
}
