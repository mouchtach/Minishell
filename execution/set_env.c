/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:31:10 by ymouchta          #+#    #+#             */
/*   Updated: 2025/05/13 23:48:34 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void  add_back(t_env **list,  t_env *new)
{
    if(!list)
        return ;
    if(!(* list ))
    {
        (* list) = new; 
        return;
    }
    t_env *tmp = * list;
    while(tmp->next)
        tmp = tmp->next;
    tmp->next = new; 
}

static t_env   *creat_new(char *value , char *key)
{
    t_env *new;

    new = NULL;
    new = malloc(sizeof(t_env));
    new->key = ft_strdup(key);
    new->value = ft_strdup(value);
    new->next = NULL;
    return(new);
}

t_env *set_env(char **env)
{
    t_env *v = NULL;
    int j;
    int i;
    char *value;
    char *key;

    i = 0;
    while(env[i])
    {
        j = 0;
        while(env[i][j] != '=')
            j++;
        value = ft_substr(env[i], j + 1 , ft_strlen(env[i]) - j);
        key = ft_substr(env[i], 0, j);
        add_back(&v, creat_new(value, key));
        free(value);
        free(key);
        i++;
    }
    return(v);
}
