/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:49:22 by macbookpro        #+#    #+#             */
/*   Updated: 2025/05/26 16:32:49 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ECHO

bool    check_n(char *parm)
{
    int i = 0;

    if(parm[i] == '-')
        i++;
    while(parm[i] == 'n')
        i++;
    if(parm[i] == '\0' && i >= 2)
        return (true);
    return(false);
}
void    ft_echo(char **cmd) // echo -n 
{
    int i = 1;
    int ck = 0;
    while (cmd[i] && check_n(cmd[i]))
    {
        ck = 1;
        i++;
    }
    while(cmd[i])
    {
        printf("%s", cmd[i]);
        if(cmd[i + 1])
            printf(" ");
        i++;
    }
    if(ck == 1)
        return ;
    printf("\n");
}


void    ft_pwd(t_exc *var)
{
    t_env *env;
    env = var->env;
    while (env)
    {
        if(!ft_strcmp(env->key, "PWD"))
        {      
            printf("%s\n", env->value);
            return;
        }
        env = env->next;
    }
}

void    ft_env(t_env *env)
{
    t_env *tmp;
    
    tmp = env;
    while(tmp)
    {
        printf("%s=%s\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
}

void    built_in_function(char **cmd, t_exc *var)
{
    if(ft_strcmp(cmd[0], "echo") == 0 || ft_strcmp(cmd[0], "ECHO")  == 0)
        ft_echo(cmd);
    if(ft_strcmp(cmd[0], "pwd") == 0 || ft_strcmp(cmd[0], "PWD")  == 0)
        ft_pwd(var);
    if(ft_strcmp(cmd[0], "env") == 0 || ft_strcmp(cmd[0], "ENV")  == 0)
        ft_env(var->env);
    // if(ft_strcmp(cmd[0], "export") == 0 || ft_strcmp(cmd[0], "EXPORT")  == 0)
    //     ft_export(var);

}