/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:38:12 by ymouchta          #+#    #+#             */
/*   Updated: 2025/06/21 13:41:24 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void f_node_t_list(t_list *node)
{
    if(!node)
    {   
        if(node->key)
        free(node->key);
        if(node->value)
        free(node->value);
        free(node);
    }
}
void f_clear_t_list(t_list **head)
{
    t_list *current;
    t_list *next;

    if (!head || !*head)
        return;

    current = *head;
    while (current)
    {
        next = current->next;
        f_node_t_list(current);
        current = next;
    }
    *head = NULL;
}