/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:33:23 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/03 16:35:16 by ymouchta         ###   ########.fr       */
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

void  list_add_back(t_list **list,  t_list *new)
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