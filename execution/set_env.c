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

void    set_value_key(char *line, char **key, char **value)
{
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

t_list   *creat_new_env(char *value , char *key, bool eg)
{
    t_list *new;

    new = NULL;
    new = malloc(sizeof(t_list));
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

    i = 0;
    list = NULL;
    if(!env || !*env)
        return (NULL);
    while(env[i])
    {
        set_value_key(env[i], &key, &value);
        if(ft_strcmp("OLDPWD", key))
            add_back_env(&list, creat_new_env(value, key, true));
        else
            add_back_env(&list, creat_new_env("", key, true));
        free(key);
        free(value);
        i++;
    }
    return (list);
}
