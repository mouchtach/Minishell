/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:52:21 by ymouchta          #+#    #+#             */
/*   Updated: 2025/06/19 16:20:33 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void init_shell_fds(t_shell *shell)
{
    shell->std_backup[0] = dup(STDIN_FILENO);   // Backup stdin
    shell->std_backup[1] = dup(STDOUT_FILENO);  // Backup stdout
    if (shell->std_backup[0] == -1 || shell->std_backup[1] == -1) {
        perror("minishell: dup failed");
        exit(0);
    }
}

void cleanup_shell_fds(t_shell *shell)
{
    close(shell->std_backup[0]);
    close(shell->std_backup[1]);
}

void reset_stdin(t_shell *shell)
{
    if (dup2(shell->std_backup[0], STDIN_FILENO) == -1)
        perror("minishell: stdin reset failed");
    if (dup2(shell->std_backup[1], STDOUT_FILENO) == -1)
        perror("minishell: stdout reset failed");
}

bool    set_input(t_cmd *command, t_redirec *in)
{

    if(command->fd_io[0] != STDIN_FILENO)
        close(command->fd_io[0]);
    if(in->type == D_INFILE)
    {
        command->fd_io[0] = open(in->name , O_RDONLY , 0777);
        if(command->fd_io[0] == -1)
            return(perror(in->name), false);
    }
    else
    {
        command->fd_io[0] = command->fd_herdoc[0];
    }
    return (true);
}

bool    set_output(t_cmd *command, t_redirec *out)
{
    if(command->fd_io[1] != STDOUT_FILENO)
        close(command->fd_io[1]);
    if(out->type == D_OUTFILE)
    {
        command->fd_io[1] = open(out->name , O_CREAT | O_TRUNC | O_RDWR , 0777);
        if(command->fd_io[1] == -1)
            return(perror("open output faild"), false);
    }
    else
    {
        command->fd_io[1] = open(out->name, O_CREAT | O_APPEND | O_RDWR , 0777);
        if(command->fd_io[1] == -1)
            return(perror("open output faild"), false);
    }
    return (true);
}

bool    set_redirection(t_cmd *command) // this fuction for list redirection in and out same list
{

    t_redirec *tmp;
    tmp = command->redirec;

    command->fd_io[0] = STDIN_FILENO; // Default input
    command->fd_io[1] = STDOUT_FILENO; // Default output

    while(tmp)
    {
        if(tmp->type == D_INFILE || tmp->type == D_HERDOC)
            if(!set_input(command, tmp))
                return(false);
        if(tmp->type == D_OUTFILE || tmp->type == D_APPEND)
            if(!set_output(command, tmp))
                return(false);
        tmp = tmp->next;
    }
    return (true);
}

bool    set_pip(t_cmd *command)
{
    if(command->fd_io[1] != STDOUT_FILENO && command->fd_pip[1] > 0)
        close(command->fd_pip[1]);

    else if(command->fd_io[1] == STDOUT_FILENO && command->next  &&command->fd_pip[1] > 0)
        command->fd_io[1] = command->fd_pip[1];
    if(command->prev && command->fd_io[0] == STDIN_FILENO)
        command->fd_io[0] = command->prev->fd_pip[0];
    if(command->fd_pip[0] != 0)
        close(command->fd_pip[0]);
    return (true);
}
bool    ft_dup_std(t_cmd *cmd)
{
    if(cmd->fd_io[0] != STDIN_FILENO)
    {
        if(dup2(cmd->fd_io[0], STDIN_FILENO) == -1)
            return (false);
        close(cmd->fd_io[0]);
    }
    if (cmd->fd_io[1] != STDOUT_FILENO)
    {
        if(dup2(cmd->fd_io[1], STDOUT_FILENO) == -1 )
            return (false);
        close(cmd->fd_io[1]);
    }
    return(true);
}
void    child_process(t_shell *val, t_cmd *cmd)
{
    char *path;

    if(!set_redirection(cmd))
        exit(1);
    if(!set_pip(cmd))
        exit(1);
    if(!ft_dup_std(cmd))
         exit(1);
    cleanup_shell_fds(val);
    if(is_built(cmd->cmd[0]))
    {
        built_in_function(cmd->cmd, val);
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
        if(list->next)
            pipe(list->fd_pip);
        fork_pid = fork();
        if(fork_pid < 0)
            perror("");
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
void    start_execution(t_shell *val)
{

    ft_herdoc(val);
    init_shell_fds(val);

    if (is_built(val->list->cmd[0]) && !val->list->next)
    {
        if(!set_redirection(val->list))
            exit(1);
        if(!set_pip(val->list))
            exit(1);
        if(!ft_dup_std(val->list))
             exit(1);
        built_in_function(val->list->cmd, val);
    }
    else
    {
        ft_fork(val);
    }
    cleanup_shell_fds(val);
}
