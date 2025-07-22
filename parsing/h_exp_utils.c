/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_exp_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:12:30 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/07/21 19:34:25 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*exit_stats(t_exp *exp)
{
	char	*exit_status_str;

	exit_status_str = ft_itoa(g_exit_status);
	if (!exit_status_str)
		return (exp->result[exp->j++] = '0', exp->i += 2, NULL);
	exp->j += ft_strlen(exit_status_str);
	exp->i += 2;
	return (ft_strdup(ft_strcat(exit_status_str, "\n")));
}
