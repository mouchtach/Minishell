/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:34:20 by ymouchta          #+#    #+#             */
/*   Updated: 2025/05/12 20:35:47 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exc.h"
t_redirec *creat_list_re(char *name , t_type t ,t_redirec *nxt )
{
    t_redirec *node;

    node = malloc(sizeof (t_redirec));
    node->name = ft_strdup(name);
    node->type = t;
    node->next = nxt;
    return (node);
}

t_cmd *set_struct(void)
{

    t_cmd *list;
    t_cmd *list2;

    t_redirec *red1;
    t_redirec *red2;

//cmd 1 ;
// input files;
    red2 = creat_list_re("ot", D_HERDOC, NULL);
    red1 = creat_list_re("in", D_FILE, red2);
// output files;

    list2 = malloc (sizeof(t_cmd));
    list2->cmd = ft_split("grep hello", ' ');
    list2->input = NULL;
    list2->output = creat_list_re("out", D_FILE, NULL);
    list2->next =  NULL;
    list = malloc (sizeof(t_cmd));
    list->cmd = ft_split("cat -e", ' ');
    list->input = red1;
    list->output = creat_list_re("out", D_FILE, NULL);
    list->next = list2;
    return (list);
}