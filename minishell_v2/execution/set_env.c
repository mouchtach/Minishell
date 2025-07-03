/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouchtach <mouchtach@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:31:10 by ymouchta          #+#    #+#             */
/*   Updated: 2025/05/28 12:01:47 by mouchtach        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"




int list_size(t_list *list)
{
    int i = 0;
    t_list *tmp;

    tmp = list;
    while(tmp)
    {
        i++;
        tmp = tmp->next;
    }
    return(i);
}


char **build_environment_array(t_list *list)
{
    int len;
    t_list *tmp;
    int i = 0;
    char *join;

    len = list_size(list);
    tmp = list;
    char **env = malloc(sizeof (char *) * (len + 1));
    if(!env)
        error_message(errno, NULL);
    while(tmp)
    {
        if(tmp->eg)
            join = ft_strjoin(tmp->key, "=");
        else
            join = tmp->key;
        env[i] = ft_strjoin(join, tmp->value);
        if(join)
            free(join);
        i++;
        tmp = tmp->next;
    }
    env[i] = NULL;
    return(env);
}

char *add_shlvl(char *value)
{
    int nm = ft_atoi(value);

    nm += 1;

    char ret[10];
    char vers[10];
    int i = 0;
    int j = 0;
    while(nm > 0)
    {
        ret[i++] = (nm % 10) + 48;
        nm /= 10;
    }
    i--;
    while(i >= 0)
        vers[j++] = ret[i--];
    vers[j] = 0;
    return(ft_strdup(vers));
}


void    set_value_key(char *line, char **key, char **value)
{
    *key = NULL;
    *value = NULL;


    if(!line || !*line)
        return;
    int i = 0;
    while(line[i] && line[i] != '=')
        i++;
    if(line[i] == '=')
    {
        *key = ft_substr(line, 0, i);
        *value = ft_strdup(line + i + 1);
    }
    else
        *key = ft_substr(line, 0, i);
}

void  add_back_env(t_list **list,  t_list *new)
{
    if(!list)
        return ;
    if(!(* list))
    {
        (* list) = new;
        return;
    }
    t_list *tmp = * list;
    while(tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

t_list   *list_new_node(char *value , char *key, bool eg)
{
    t_list *new;

    new = NULL;
    new = malloc(sizeof(t_list));
    if(!new)
        return(error_message(errno, NULL), NULL);
    new->key = ft_strdup(key);
    new->value = ft_strdup (value);
    new->eg = eg;
    new->next = NULL;
    return(new);
}

t_list *set_env(char **env)
{
    t_list  *list;
    int     i;
    char    *key;
    char    *value;
    char    *shell_lvl;

    i = 0;
    list = NULL;
    while(env[i])
    {
        set_value_key(env[i], &key, &value);
        if(!ft_strcmp(key, "OLDPWD"))
            add_back_env(&list, list_new_node("", key, false));
        else if(!ft_strcmp(key, "SHLVL"))
        {
            shell_lvl = add_shlvl(value);
            add_back_env(&list, list_new_node(shell_lvl, key, true));
            free(shell_lvl);
        }
        else
            add_back_env(&list, list_new_node(value, key, true));
        free(key);
        if(value)
            free(value);
        i++;
    }
    return (list);
}

void    add_default_env(t_list **list)
{
    char *pwd;

    pwd = NULL;
    if(!get_value(*list, "SHLVL"))
        add_back_env(list, list_new_node("1", "SHLVL",  true));
    if(!get_value(*list, "PWD"))
    {
        pwd = getcwd(NULL, 0);
        add_back_env(list, list_new_node(pwd, "PWD",  true));
        free(pwd);
    }
    if(!get_value(*list, "_"))
        add_back_env(list, list_new_node("/usr/bin/env", "_",  true));
    if(!get_value(*list, "OLDPWD"))
        add_back_env(list, list_new_node("", "OLDPWD",  false));
}

t_list *environment(char **env)
{
    t_list *list;

    list = NULL;
    if(!env || !*env)
        add_default_env(&list);
    else
    {
        list = set_env(env);
        add_default_env(&list);
    }
    return (list);
}
