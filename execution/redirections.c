/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 21:45:30 by ymouchta          #+#    #+#             */
/*   Updated: 2025/06/21 13:31:56 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

bool    set_pip(t_cmd *command)
{
    // in this condition  i check if we have file we need close pipe
    if(command->fd_io[1] != STDOUT_FILENO && command->fd_pip[1] > 0)
        close(command->fd_pip[1]);
    // in this case
    else if(command->fd_io[1] == STDOUT_FILENO && command->next  &&command->fd_pip[1] > 0)
        command->fd_io[1] = command->fd_pip[1];
    if(command->prev && command->fd_io[0] == STDIN_FILENO)
        command->fd_io[0] = command->prev->fd_pip[0];
    // if(command->fd_pip[0] != 0)
    //     close(command->fd_pip[0]);
    return (true);
}

bool    ft_dup_std(t_cmd *cmd)
{
    if(cmd->fd_io[0] != STDIN_FILENO)
    {
        if(dup2(cmd->fd_io[0], STDIN_FILENO) == -1)
            return (close(cmd->fd_io[0]), false);
        close(cmd->fd_io[0]);
    }
    if (cmd->fd_io[1] != STDOUT_FILENO)
    {
        if(dup2(cmd->fd_io[1], STDOUT_FILENO) == -1 )
            return (close(cmd->fd_io[1]), false);
        close(cmd->fd_io[1]);
    }
    return(true);
}

bool    set_input(t_cmd *command, t_redirec *in)
{

    // in this condition if realy open file input and find next file we need close old one
    if(command->fd_io[0] != STDIN_FILENO && command->fd_herdoc[0] == -1)
        close(command->fd_io[0]);
    if(in->type == D_INFILE)
    {
        command->fd_io[0] = open(in->name , O_RDONLY , 0777);
        if(command->fd_io[0] == -1)
            return(perror(OPEN_FAILD), false);
    }
    else
        command->fd_io[0] = command->fd_herdoc[0];
    return (true);
}

bool    set_output(t_cmd *command, t_redirec *out)
{
    // in this condition if realy open file output and find next file we need close old one
    if(command->fd_io[1] != STDOUT_FILENO)
        close(command->fd_io[1]);
    if(out->type == D_OUTFILE)
    {
        command->fd_io[1] = open(out->name , O_CREAT | O_TRUNC | O_RDWR , 0777);
        if(command->fd_io[1] == -1)
            return(perror(OPEN_FAILD), false);
    }
    else
    {
        command->fd_io[1] = open(out->name, O_CREAT | O_APPEND | O_RDWR , 0777);
        if(command->fd_io[1] == -1)
            return(perror(OPEN_FAILD), false);
    }
    return (true);
}

bool    set_redirection(t_cmd *command) // this fuction for list redirection in and out same list
{

    t_redirec *tmp;
    tmp = command->redirec;

    // set to stander 0 1
    command->fd_io[0] = STDIN_FILENO; // Default input
    command->fd_io[1] = STDOUT_FILENO; // Default output
    printf("befor set = %d\n",command->fd_io[0] );
    while(tmp)
    {
        // if have input or output redirection
        if(tmp->type == D_INFILE || tmp->type == D_HERDOC)
            if(!set_input(command, tmp))
                return(false);
        if(tmp->type == D_OUTFILE || tmp->type == D_APPEND)
            if(!set_output(command, tmp))
                return(false);
        tmp = tmp->next;
    }
    printf("after set = %d\n",command->fd_io[0] );

    return (true);
}