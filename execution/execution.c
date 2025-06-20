/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:52:21 by ymouchta          #+#    #+#             */
/*   Updated: 2025/06/20 15:28:58 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool  init_shell_fds(t_shell *shell)
{
    shell->std_backup[0] = dup(STDIN_FILENO);   // Backup stdin
    shell->std_backup[1] = dup(STDOUT_FILENO);  // Backup stdout
    if (shell->std_backup[0] == -1 || shell->std_backup[1] == -1)
        return (perror(DUP_FAILD), false);
    return (true);
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

    // in this condition if realy open file input and find next file we need close old one
    if(command->fd_io[0] != STDIN_FILENO)
        close(command->fd_io[0]);
    if(in->type == D_INFILE)
    {
        command->fd_io[0] = open(in->name , O_RDONLY , 0777);
        if(command->fd_io[0] == -1)
            return(perror(OPEN_FAILD), false);
    }
    else
    {
        command->fd_io[0] = command->fd_herdoc[0];
    }
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
    return (true);
}

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
