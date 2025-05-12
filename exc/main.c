/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:38:06 by ymouchta          #+#    #+#             */
/*   Updated: 2025/05/12 22:09:39 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exc.h"

int main(int ac, char **av, char **env)
{
    t_exc *val;
    char **path;

    val->list = set_struct();
    val->env = set_env(env);
    val->path = set_path(val->env);
    // if(!excution(val))
    //     return(1);

}