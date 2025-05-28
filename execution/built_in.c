/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:49:22 by macbookpro        #+#    #+#             */
/*   Updated: 2025/05/28 17:12:09 by ymouchta         ###   ########.fr       */
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


void    ft_pwd(t_shell *var)
{
    t_list *env;
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

void    ft_list(t_list *env)
{
    t_list *tmp;
    
    tmp = env;
    while(tmp)
    {
        printf("%s=%s\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
}


void    desplay_list(t_list *list)
{
    while(list)
    {
        printf("key = %s, value = %s\n", list->key, list->value);
        list = list->next;
    }
}

t_list *ft_copy_env(t_list *env)
{
    t_list *list;
    t_list *new = NULL;

    list = env;

    while(list)
    {
        add_back_env(&new, creat_new_env(list->value, list->key));
        list = list->next;
    }
    return(new);
}


void    ft_export(t_list *env)
{
    t_list *new = NULL;

    new = ft_copy_env(env);
    desplay_list(new);
    // ft_swap(&new, "PATH", "PWD");
    printf("\nAfter swapping:\n");
    desplay_list(new);

    // ft_sort_list(&new);
    
}
void    update_env(char *key, char *value, t_list *env)
{
    t_list *tmp;

    tmp = env;
    while(tmp)
    {
        if(!ft_strcmp(tmp->key, key))
        {
            free(tmp->value);
            tmp->value = ft_strdup(value);
            return;
        }
        tmp = tmp->next;
    }
}
char    *get_old_pwd(t_list *env, char *key)
{
    t_list *tmp;

    tmp = env;
    while(tmp)
    {
        if(!ft_strcmp(tmp->key, key))
            return(tmp->value);
        tmp = tmp->next;
    }
    return (NULL);
}
void    ft_cd(t_list *env, char *path)
{
    char *oldpwd;
    char *buffer;
    char *ret;

    if(!path)
        return;
    oldpwd = getcwd(NULL, 0);
    if(!oldpwd)
        return(perror("getcwd"));
    if(!ft_strcmp(path, "-"))
    {
        ret = get_old_pwd(env, "OLDPWD");
        if(chdir(ret) == -1)
            return(free(oldpwd), perror("cd"));
    }
    else if((!ft_strcmp(path, "~") )|| (!ft_strcmp(path, "--")))
    {
        ret = get_old_pwd(env, "HOME");
        if(chdir(ret) == -1)
            return(free(oldpwd), perror("cd"));
    }
    else
    {
        if(chdir(path) == -1)
            return(free(oldpwd), perror("cd"));
    }
    buffer = getcwd(NULL, 0);
    if(!buffer)
        return(free(oldpwd), perror("getcwd"));//  free buffer
    update_env("PWD", buffer, env);
    update_env("OLDPWD",oldpwd, env);
    free(buffer);
    free(oldpwd);
}

void    built_in_function(char **cmd, t_shell *var)
{
    if(ft_strcmp(cmd[0], "echo") == 0 || ft_strcmp(cmd[0], "ECHO")  == 0)
        ft_echo(cmd);
    if(ft_strcmp(cmd[0], "pwd") == 0 || ft_strcmp(cmd[0], "PWD")  == 0)
        ft_pwd(var);
    if(ft_strcmp(cmd[0], "env") == 0 || ft_strcmp(cmd[0], "ENV")  == 0)
        ft_list(var->env);
    if(ft_strcmp(cmd[0], "export") == 0 || ft_strcmp(cmd[0], "EXPORT")  == 0)
        ft_export(var->env);
    if(ft_strcmp(cmd[0], "cd") == 0 || ft_strcmp(cmd[0], "CD")  == 0)
        ft_cd(var->env, cmd[1]);
        
}