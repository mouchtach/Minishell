/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_cpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:55:26 by ymouchta          #+#    #+#             */
/*   Updated: 2025/05/16 12:18:44 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    add_back_rederc(t_redirec **list, t_redirec *new)
{
    if (!list)
        return;

    if (!*list)
    {
        *list = new;
        return;
    }

    t_redirec *tmp = *list;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    new->next = NULL;
}

void    add_back_cmd(t_cmd **list, t_cmd *new)
{
    if(!*list)
    {
        *list = new;
        return ;
    }
    t_cmd *tmp;
    tmp = *list;
    while(tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    new->next = NULL;
    new->prev = tmp;
}


t_redirec *creat_new_rederc(t_redi_list *redrc)
{
    t_redirec *new;

    new = malloc(sizeof(t_redirec));
    new->name = redrc->file;
    if(redrc->type == INPUT)
        new->type = D_IN;
    else if(redrc->type == OUTPUT)
        new->type = D_OUT;
    else if(redrc->type == HEREDOC)
        new->type = D_HERDOC;
    else if(redrc->type == APPEND)
        new->type = D_APPEND;
    new->next = NULL;
    return(new);    
}
t_cmd *creat_new_cmd(t_cmdarg *old_strct, t_redirec *my_in_list, t_redirec *my_out_list)
{
    t_cmd *new;

    new = malloc(sizeof(t_cmd));
    new->cmd = old_strct->cmd;
    new->input = my_in_list;
    new->output = my_out_list;
    new->next = NULL;
    new->prev = NULL;
    return(new);
}
void desplay_this_node(t_cmd *list)
{
    t_redirec *tmp;
    while(list)
    {
        printf("cmd = %s\n", list->cmd[0]);
        tmp = list->input;
        while(tmp)
        {
            printf("input = %s\n", tmp->name);
            tmp = tmp->next;
        }
        tmp = list->output;
        while(tmp)
        {
            printf("output = %s\n", tmp->name);
            tmp = tmp->next;
        }
        list = list->next;
    }
}

t_cmd *set_strct(t_cmdarg *old_strct)
{
    int i;
    i = 0;
    t_cmd *list = NULL;
    t_redirec *my_in_list = NULL;
    t_redirec *my_out_list = NULL;
    t_redi_list *redrc_in;
    t_redi_list *redrc_out;

    t_redi_list *tmp;
    while(old_strct)
    {
        tmp = old_strct->input;
        while(tmp)
        {
            add_back_rederc(&my_in_list, creat_new_rederc(tmp));
            tmp = tmp->next;
        }
        tmp = old_strct->output;
        while(tmp)
        {
            add_back_rederc(&my_out_list, creat_new_rederc(tmp));
            tmp = tmp->next;
        }
        add_back_cmd(&list, creat_new_cmd(old_strct, my_in_list, my_out_list));
        my_in_list = NULL;
        my_out_list = NULL;
        old_strct = old_strct->next;
    }
    // desplay_this_node(list);
    return(list);
}

t_exc   *strct_copy(t_cmdarg    *old_strct, char **env)
{
    t_exc *var;

    var = malloc(sizeof(t_exc));
    var->list = set_strct(old_strct);
    var->env = set_env(env);
    var->path = set_path(var->env);

    return (var);
}