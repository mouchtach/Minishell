/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   desplay_my_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:52:20 by ymouchta          #+#    #+#             */
/*   Updated: 2025/05/14 10:10:25 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    desplay_my_list(t_cmd *list)
{
    t_cmd *tmp;
    t_redirec *tmp2;

    tmp = list;
    while(tmp)
    {
        printf("cmd: ");
        for(int i = 0; tmp->cmd[i]; i++)
            printf("%s ", tmp->cmd[i]);
        printf("\n");
        tmp2 = tmp->input;
        while(tmp2)
        {

            if (tmp2->type == D_IN)
                printf("input : %s  > type: D_IN\n", tmp2->name);
            else if (tmp2->type == D_OUT)
                printf("input : %s  > type: D_OUT\n", tmp2->name);
            else if (tmp2->type == D_APPEND)
                printf("input : %s  > type: D_APPEND\n", tmp2->name);
            else if (tmp2->type == D_HERDOC)
                printf("input : %s  > type: D_HERDOC\n", tmp2->name);

            tmp2 = tmp2->next;
        }
        tmp2 = tmp->output;
        while(tmp2)
        {
            if (tmp2->type == D_IN)
                printf("output : %s  > type: D_IN\n", tmp2->name);
            else if (tmp2->type == D_OUT)
                printf("output : %s  > type: D_OUT\n", tmp2->name);
            else if (tmp2->type == D_APPEND)
                printf("output : %s  > type: D_APPEND\n", tmp2->name);
            else if (tmp2->type == D_HERDOC)
                printf("output : %s  > type: D_HERDOC\n", tmp2->name);
            tmp2 = tmp2->next;
        }
        tmp = tmp->next;
    }
    
}