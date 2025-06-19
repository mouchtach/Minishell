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
// int	ft_lstsize_env(t_list *lst)
// {
// 	t_list	*p;
// 	int		len;

// 	if (lst == NULL)
// 		return (0);
// 	p = lst;
// 	len = 0;
// 	while (p != NULL)
// 	{
// 		p = p->next;
// 		len++;
// 	}
// 	return (len);
// }


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
    new->prev = tmp;
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
    new->prev = NULL;
    return(new);
}

t_list *set_env(char **env)
{
    if(!env || !*env)
        return (NULL);

    t_list *list;
    int i;
    char *key;
    char *value;

    list = NULL;
    i = 0;
    int k = 0;
    while(env[i])
    {
        k = 0;
        while(env[i][k] && env[i][k] != '=')
            k++;
        if(k == 0)
        {
            i++;
            continue;
        }
        key = ft_substr(env[i], 0, k);
        if(!key)
            return (NULL);
        value = ft_substr(env[i], k + 1, ft_strlen(env[i]) - k - 1);
        if(!value)
        {
            free(key);
            return (NULL);
        }
        if(ft_strcmp("OLDPWD", key))
            add_back_env(&list, creat_new_env(value, key, true));
        free(key);
        free(value);
        i++;
    }
    return (list);
}
