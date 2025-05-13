/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 23:55:58 by ymouchta          #+#    #+#             */
/*   Updated: 2025/05/13 00:33:56 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "exc.h"
void    herdoc_read(char *dlm)
{
    int fd;
    fd = open("/tmp/.herdoc", O_CREAT | O_TRUNC | O_RDWR , 0777);
    while(1)
    {}
    
}

bool    check_herdoc(t_exc *val)
{
    // t_cmd *cmd_tmp;
    // t_redirec *red_tmp;
    // cmd_tmp = val->list;
    // while(cmd_tmp)
    // {
    //     red_tmp = cmd_tmp->input;
    //     while(red_tmp)
    //     {
    //         if(red_tmp->type == D_HERDOC)
    //         12R543` tjhfgdvxzevrw
            
    //     }
    // }
    
}

int     herdoc_file(t_exc *val)
{
    t_cmd *tmp;
    t_redirec *tmp_red;
    tmp = val->list;
    
    while(tmp)
    {
        tmp_red = tmp->input; 
        while(tmp_red)
        {
            if(tmp_red->type == D_HERDOC)
                herdoc_read(tmp_red->name);
        }
        
    }
    
    
    
    
}

void    Redirections(t_exc *val)
{
    // if(check_herdoc(val))


    
}