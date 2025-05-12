/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 21:16:33 by ymouchta          #+#    #+#             */
/*   Updated: 2025/05/12 21:26:17 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exc.h"

char **set_path(t_env *v)
{
    t_env *tmp;

    tmp = v;
    if(!tmp)
        return (NULL);
    while(ft_strcmp(tmp->key, "PATH"))
        tmp = tmp->next;
    return(ft_split(tmp->value, ':'));
}