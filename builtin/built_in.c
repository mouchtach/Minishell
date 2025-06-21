/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:49:22 by macbookpro        #+#    #+#             */
/*   Updated: 2025/06/21 10:49:51 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    is_built(char *cmd)
{
    if(ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "ECHO")  == 0)  // unset
        return(1);
    if(ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "PWD")  == 0)
        return(1);
    if(ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "ENV")  == 0)
        return(1);
    if(ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "EXPORT")  == 0)
        return(1);
    if(ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "CD")  == 0)
        return(1);
    if(ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "UNSET")  == 0)
        return(1);
    if(ft_strcmp(cmd, "exit") == 0 || ft_strcmp(cmd, "EXIT")  == 0)
        return(1);
    return(0);
}

void    ft_list(t_list *env)
{
    t_list *tmp;

    tmp = env;
    while(tmp)
    {
        if(tmp->eg == true)
            printf("%s=%s\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
}



void    ft_unset(t_shell *val, char **cmd)
{
    int j = 1;
    t_list *curr;
    t_list *prev;
    t_list *tmp;

    while(cmd[j])
    {
        curr = val->env;
        prev = NULL;
        while (curr)
        {
            if (!ft_strcmp(cmd[j], curr->key))
            {
                tmp = curr->next;
                if (prev == NULL)
                    val->env = tmp;
                else
                    prev->next = tmp;
                f_node_t_list(curr);
                curr = tmp;
            }
            else
            {
                prev = curr;
                curr = curr->next;
            }
        }
        j++;
    }
}

bool    built_in_function(char **cmd, t_shell *val)
{
    if(ft_strcmp(cmd[0], "echo") == 0 || ft_strcmp(cmd[0], "ECHO")  == 0)
        ft_echo(cmd);
    if(ft_strcmp(cmd[0], "pwd") == 0 || ft_strcmp(cmd[0], "PWD")  == 0)
        printf("%s\n", get_value(val->env, "PWD"));
    if(ft_strcmp(cmd[0], "env") == 0 || ft_strcmp(cmd[0], "ENV")  == 0)
        ft_list(val->env);
    if(ft_strcmp(cmd[0], "export") == 0 || ft_strcmp(cmd[0], "EXPORT")  == 0)
        ft_export(val, cmd);
    if(ft_strcmp(cmd[0], "cd") == 0 || ft_strcmp(cmd[0], "CD")  == 0)
        ft_cd(val->env, cmd[1]);
    if(ft_strcmp(cmd[0], "unset") == 0 || ft_strcmp(cmd[0], "UNSET")  == 0)
        ft_unset(val, cmd);
    if(ft_strcmp(cmd[0], "exit") == 0 || ft_strcmp(cmd[0], "EXIT")  == 0)
        exit(0);
    return(true);
}
