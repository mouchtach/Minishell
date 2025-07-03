/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:57:16 by ymouchta          #+#    #+#             */
/*   Updated: 2025/06/21 13:42:55 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list *ft_copy_env(t_list *env)
{
    t_list *list;
    t_list *new = NULL;

    list = env;
    while(list)
    {
        add_back_env(&new, creat_new_env(list->value, list->key, list->eg));
        list = list->next;
    }
    return(new);
}

int    add_export_list(t_list **env,char *value, char *key, bool eg)
{
    t_list *tmp;

    tmp = *env;
    while(tmp)
    {
        if(!ft_strcmp(tmp->key, key))
        {
            free(tmp->value);
            tmp->value = value;
            return (0);
        }
        tmp = tmp->next;
    }
    add_back_env(env, creat_new_env(value, key , eg));
    return(1);

}

void    desplay_list_export(t_list *list)
{
    t_list *tmp;

    tmp = list;
    while(tmp)
    {
        if(tmp->eg == true)
            printf("%s='%s'\n", tmp->key, tmp->value);
        else
            printf("%s\n", tmp->key);
        tmp = tmp->next;
    }
}

void sort_export(t_list *var)
{
    t_list *new = NULL;
    t_list *tmp;
    t_list *tmp2;
    t_list *small;

    new = ft_copy_env(var);
    tmp = new;
    while (tmp)
    {
        small = tmp;
        tmp2 = tmp->next;
        while (tmp2)
        {
            if (ft_strcmp(tmp2->key, small->key) < 0)
                small = tmp2;
            tmp2 = tmp2->next;
        }
        if (small != tmp)
        {
            char *temp_key = tmp->key;
            bool eg = tmp->eg;
            char *temp_value = tmp->value;
            tmp->key = small->key;
            tmp->value = small->value;
            tmp->eg = small->eg;
            small->key = temp_key;
            small->value = temp_value;
            small->eg = eg;
        }
        tmp = tmp->next;
    }
    desplay_list_export(new);
    //clear list
    f_clear_t_list(&new);
}

void    ft_export(t_shell *var, char **cmd)
{
    bool eg = false;
    char *value;
    char *key;

    int j = 1;
    if(!cmd[j])
        sort_export(var->env);
    while(cmd[j])
    {
        int i = 0;
        while(cmd[j][i] && cmd[j][i] != '=')
            i++;
        if(cmd[j][i] == '=')
        {
            value = ft_strdup(cmd[j] + i + 1);
            eg = true;
        }
        else
            value = ft_strdup(cmd[j] + i);
        key = ft_substr(cmd[j], 0, i);
        if(!add_export_list(&var->env, value, key, eg))
            free(value);
        else
        {
            free(value);
            free(key);
        }
        j++;
    }
}