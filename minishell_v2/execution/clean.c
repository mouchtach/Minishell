/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:38:12 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/03 14:21:16 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void close_fd(int *fd)
{
    close(*fd);
    *fd = -1;
}


void clear_all_pipes(t_cmd *cmd)
{
    t_cmd *current;
    // t_cmd *next;

    if (!cmd)
        return;

    current = cmd;
    while (current)
    {
        if (current->fd_pip[0] > 0)
            close(current->fd_pip[0]);
        if (current->fd_pip[1] > 0)
            close(current->fd_pip[1]);
        if (current->fd_herdoc[0] > 0)
            close(current->fd_herdoc[0]);
        if (current->fd_io[0] > 0)
            close(current->fd_io[0]);
        current = current->next;
    }
}

void cleanup_shell(t_shell *shell)
{
    clear_all_pipes(shell->list);
    free_list(&shell->env);
    cmdfree(shell->list);
    free(shell);
    shell = NULL;
}


void free_list_node(t_list *node)
{
    if (node)
    {
        if (node->key)
            free(node->key);
        if (node->value)
            free(node->value);
        free(node);
    }
    node = NULL;
}

void free_list(t_list **head)
{
    t_list *current;
    t_list *next;

    if (!head || !*head)
        return;

    current = *head;
    while (current)
    {
        next = current->next;
        free_list_node(current);
        current = next;
    }
    *head = NULL;
}