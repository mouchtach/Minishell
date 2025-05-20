/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:20:39 by ymouchta          #+#    #+#             */
/*   Updated: 2025/05/20 17:02:27 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void init_shell_fds(t_exc *shell)
{
    shell->std_backup[0] = dup(STDIN_FILENO);   // Backup stdin
    shell->std_backup[1] = dup(STDOUT_FILENO);  // Backup stdout
    if (shell->std_backup[0] == -1 || shell->std_backup[1] == -1) {
        perror("minishell: dup failed");
        exit(0);
    }
}

void reset_stdin(t_exc *shell)
{
    if (dup2(shell->std_backup[0], STDIN_FILENO) == -1)
        perror("minishell: stdin reset failed");
    if (dup2(shell->std_backup[1], STDOUT_FILENO) == -1)
        perror("minishell: stdout reset failed");

    // Optional: Close backups if you want to be strict
    // close(shell->std_backup[0]);
    // close(shell->std_backup[1]);
}

bool    set_input(t_cmd *command, t_redirec *in)
{
    if(command->fd_io[0] != STDIN_FILENO)
    {
        printf("%sCHILD ///////// CLOSE command->fd_io[0] \n%s",RED, RESET);
        close(command->fd_io[0]);
    }
    if(in->type == D_IN)
    {
        printf("%sCHILD ///////// OPEN D_IN  command->fd_io[0] = %s  \n%s",RED,in->name , RESET);
        command->fd_io[0] = open(in->name , O_RDONLY , 0777);
        if(command->fd_io[0] == -1)
            return(perror(""), false);
    }
    else
    {
        printf("%sCHILD ///////// OPEN D_HERDOC  command->fd_io[0] = HERDOC  \n%s",RED, RESET);
        command->fd_io[0] = open(HEREDOC_FILE, O_RDONLY , 0777);
        if(command->fd_io[0] == -1)
            return(perror(""), false);
    }
    return (true);
}

bool    set_output(t_cmd *command, t_redirec *out)
{
    if(command->fd_io[1] != STDOUT_FILENO)
    {
        printf("%sCHILD ///////// CLOSE command->fd_io[1] %s\n",RED, RESET);
        close(command->fd_io[1]);
    }
    if(out->type == D_OUT)
    {
        printf("%sCHILD ///////// OPEN D_OUT  command->fd_io[1] = %s  %s\n",RED,out->name , RESET);
        command->fd_io[1] = open(out->name , O_CREAT | O_TRUNC | O_RDWR , 0777);
        if(command->fd_io[1] == -1)
            return(perror(""), false);
    }
    else
    {
        printf("%sCHILD ///////// OPEN D_APPEND  command->fd_io[1] = %s  %s\n",RED,out->name , RESET);
        command->fd_io[1] = open(out->name, O_CREAT | O_APPEND | O_RDWR , 0777);
        if(command->fd_io[1] == -1)
            return(perror(""), false);
    }
    return (true);
}

bool    set_redirection(t_cmd *command) // this fuction for list redirection in and out same list
{
    command->fd_io[0] = STDIN_FILENO;
    command->fd_io[1] = STDOUT_FILENO;
    printf("%sCHILD ///////// command->fd_io[1]  = STDOUT_FILENO \n%s",RED, RESET);
    printf("%sCHILD ///////// command->fd_io[0]  = STDIN_FILENO \n%s",RED, RESET);


    printf("SET_REDERCTIO\n");
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
    return (true);
}

bool    set_set_red(t_cmd *command) // this fuction for  tow list in_list and out_list
{
    command->fd_io[0] = STDIN_FILENO;
    command->fd_io[1] = STDOUT_FILENO;

    printf("%sCHILD ///////// command->fd_io[1]  = STDOUT_FILENO %s\n",RED, RESET);
    printf("%sCHILD ///////// command->fd_io[0]  = STDIN_FILENO %s\n",RED, RESET);

    t_redirec *tmp;
    tmp = command->input;
    while(tmp)
    {
        if(!set_input(command, tmp))
            return(false);
        tmp = tmp->next;
    }
    tmp = command->output;
    while(tmp)
    {
        if(!set_output(command, tmp))
            return(false);
        tmp = tmp->next;
    }
    return(true);
}

bool    set_pip(t_cmd *command)
{
    if(command->fd_io[1] != STDOUT_FILENO && command->fd_pip[1] > 0)
    {
        printf("%sCHILD ///////// CLOSE PIP [1]  %s\n",RED, RESET);
        close(command->fd_pip[1]);
    }
    else if(command->fd_io[1] == STDOUT_FILENO && command->next  &&command->fd_pip[1] > 0)
    {
        printf("%sCHILD ///////// PIP command->fd_io[1] = command->fd_pip[1]%s\n",RED, RESET);
        command->fd_io[1] = command->fd_pip[1];
    }
    if(command->prev && command->fd_io[0] == STDIN_FILENO)
    {
        printf("%sCHILD ///////// PIP command->fd_io[0] = command->prev->fd_pip[0]%s\n",RED, RESET);
        command->fd_io[0] = command->prev->fd_pip[0];
    }
    if(command->fd_pip[0] != 0)
    {
        printf("%sCHILD ///////// CLOSE PIP [0]  %s\n",RED, RESET);
        close(command->fd_pip[0]);
    }
    return (true);
}

void    child_process(t_exc *val, t_cmd *cmd)
{
    char *path;

    if(!set_set_red(cmd))
    {
        perror("");
        exit(0);
    }
    set_pip(cmd);

    path = get_path_cmd(val->path, cmd->cmd[0]);
    printf("%sCHILD ///////// PATH = %s%s \n",RED,path , RESET);

    if(!path)
    {
        perror("");
        exit(0);
    }
    // printf("%sCHILD ///////// DUP2 output = = command->fd_io[1] and CLOSE %s\n",RED, RESET);
    if(cmd->fd_io[0] != STDIN_FILENO)
    {
        printf("%sCHILD ///////// DUP2 input = command->fd_io[0] and CLOSE %s\n",RED, RESET);
        // printf("%sCHILD ///////// CLOSE command->fd_io[0]  %s\n",RED, RESET);
        // close(cmd->fd_io[0]);
        dup2(cmd->fd_io[0], STDIN_FILENO);
        close(cmd->fd_io[0]);
    }
    if (cmd->fd_io[1] != STDOUT_FILENO)
    {
        printf("%sCHILD ///////// CLOSE command->fd_io[1]  %s\n",RED, RESET);
        // close(cmd->fd_io[1]);
        dup2(cmd->fd_io[1], STDOUT_FILENO);
        close(cmd->fd_io[1]);
    }
    // else
    // dup2(cmd->fd_io[1], STDOUT_FILENO);


    if(execve(path, cmd->cmd, NULL) == -1)
        perror("");
    exit(0);
}
void    parent_process(t_cmd *cmd)
{
    if(cmd->fd_pip[1] > 0)
    {
        printf("%sCLOSE cmd->fd_pip[1]  CMD = %s%s\n ", BLUE,cmd->cmd[0] ,  RESET);
        close(cmd->fd_pip[1]);
    }
    if(cmd->prev)
    {
        if(cmd->prev->prev)
        {
            if(cmd->prev->prev->fd_pip[0] > 0)
            {
                printf("%sCLOSE cmd->prev->prev->fd_pip[0]  CMD = %s%s\n ", BLUE,cmd->prev->prev->cmd[0] ,  RESET);
                close(cmd->prev->prev->fd_pip[0]);
            }
        }
    }
}
void    start_execution(t_exc *val)
{
    t_cmd *list;
    int    fork_pid;

    list = val->list;
    int i = 1;
    init_shell_fds(val);
    printf("%sSTART /////////%s\n", GREEN, RESET);


    while(list)
    {
        // print_command_tree(list, i);
        if(list->next)
        {
            printf("%sOPEND PIPES[0][1]  CMD = %s%s\n ", BLUE,list->cmd[0] ,  RESET);
            pipe(list->fd_pip);
        }
        printf("%sFORK();%s\n ", BLUE,  RESET);
        fork_pid = fork();
        if(fork_pid < 0)
            perror("");
        if(fork_pid == 0)
        {
            child_process(val, list);
        }
        if(fork_pid > 0)
            parent_process(list);
        if(list->prev)
        {
            if (list->prev->fd_pip[0] > 0)
            {
                printf("%sCLOSE list->prev->fd_pip[0]  CMD = %s%s\n ", BLUE,list->cmd[0] ,  RESET);
                close(list->prev->fd_pip[0]);
            }
        }
        reset_stdin(val);
        printf("%sRESET _ STD%s\n ", BLUE,  RESET);

        list = list->next;
    }
    while(wait(NULL) > 0);
    printf("%sEND /////////%s\n", GREEN, RESET);

}
