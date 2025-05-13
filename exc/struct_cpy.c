/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_cpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:55:26 by ymouchta          #+#    #+#             */
/*   Updated: 2025/05/14 00:36:23 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd *set_strct(t_cmdarg *old_strct)
{
    int i;
    i = 0;
    while(old_strct)
    { 
       
    }

    printf("len list = %d\n", i);
    
    return(NULL);
    
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