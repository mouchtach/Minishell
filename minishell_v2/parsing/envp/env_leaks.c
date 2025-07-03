/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_leaks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:07:41 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/06/21 15:47:18 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	env_leaks(t_list *env)
{
	t_list	*tmp;

	while (env)
	{
		p1char(&env->key);
		p1char(&env->value);
		tmp = env;
		env = env->next;
		free(tmp);
	}
}
