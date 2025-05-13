/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 23:55:58 by ymouchta          #+#    #+#             */
/*   Updated: 2025/05/13 15:34:10 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "exc.h"

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
    // exit (0);
}

void    fork_heredoc(char *delimiter)
{
    int fork_pid;

    fork_pid = fork();
    printf("creating process\n");
    if(fork_pid == 0)
    {
        herdoc_read(delimiter);
        exit(0);
    }
    if(fork_pid > 0)
    {
        waitpid(fork_pid, NULL, 0);
        printf("fork done\n");
    }
}

void   herdoc_file(t_exc *val)
{
    t_cmd *tmp;
    t_redirec *tmp_red;
    tmp = val->list;
    
    // while(tmp)
    // {
    //     printf("command = %s\n", tmp->cmd[0]);
    //     tmp_red = tmp->input;
    //     while(tmp_red)
    //     {
    //         printf("%s\n", tmp_red->name);
    //         tmp_red = tmp_red->next;
    //     }
    //     tmp = tmp->next;
    // }
    int i = 0;
    while(tmp)
    {
        printf("%s\n", tmp->cmd[0]);
        tmp_red = tmp->input; 
        while(tmp_red)
        {
            printf("%s\n", tmp_red->name);
            if(tmp_red->type == D_HERDOC)
                fork_heredoc(tmp_red->name);
            tmp_red = tmp_red->next;
            i++;
        }
        tmp = tmp->next;
    }
    printf("i = %d\n", i);
    // cat -e < in << ot << tt > out | grep hello << ph > out

    //cmd **  = "cat" , "-e";
    //t_redec  *input = (in , WORD) , (ot , HERDC) , (tt , HERDC) 
}

void    redirections(t_exc *val)
{
    herdoc_file(val);
}