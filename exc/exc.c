/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:32:48 by ymouchta          #+#    #+#             */
/*   Updated: 2025/05/16 13:40:31 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void get_origin_fd(t_cmd *list)
{
    printf("we tage origine STD\n");
    list->fd_origine[0] = dup(STDIN_FILENO);
    list->fd_origine[1] = dup(STDOUT_FILENO);
}

void set_origin_fd(t_cmd *list)
{
    printf("we reset origine STD\n");
    dup2(list->fd_origine[0], STDIN_FILENO);
    dup2(list->fd_origine[1], STDOUT_FILENO);

    close(list->fd_origine[0]);
    close(list->fd_origine[1]);
}

void    child_process(t_exc *val, t_cmd *list, int  i)
{
    if(!redirection(list))
        exit(1);
    char *path = get_path_cmd(val->path, val->list->cmd[0]);
    if(!path)
        exit(1);
    dup2(list->fd_files[0], STDIN_FILENO);
    close(list->fd_files[0]);
    dup2(list->fd_files[1], STDOUT_FILENO);
    close(list->fd_files[1]);
    close(list->fd_pip[1]);
    close(list->fd_pip[0]);
    // execve(path, list->cmd, NULL);
}
void    excution(t_exc *val)
{
    int fork_pid;
    ft_herdoc(val);

    t_cmd *f_list;

    f_list = val->list;
    int i = 1;
    while(f_list)
    {
        if(f_list->next)
        {

            if(pipe(val->list->fd_pip) == -1)
                return ;
            else
            {
                printf("PIP creat\n");
                printf("ID PIP IN = %d \n ID PIP OUT = %d\n", f_list->fd_pip[0], f_list->fd_pip[1]);
            }
        }

        fork_pid = fork();
        if(fork_pid == 0)
        {
            printf("cmd : %s\n", f_list->cmd[0]);

            child_process(val, f_list, i);
            print_command_tree(f_list, i);
            // while(1);
            exit(0);
        }
        if(fork_pid > 0)
        {
            if(val->list->next)
            {
                close(val->list->fd_pip[0]);
                close(val->list->fd_pip[1]);
            }

        }
        if(fork_pid < 0)
        {
            perror("fork");
            exit(1);
        }
        f_list = f_list->next;
        i++;
    }
    while(wait(NULL) > 0);
    unlink(HEREDOC_FILE);
}



