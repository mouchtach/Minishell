/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 16:38:33 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/08 23:24:22 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	set_new_content(t_token **token, t_exp *exp, t_ambg *amb)
{
	if (count_word(exp->value) > 1 && amb->ambiguous)
	{
		(*token)->amb = 1;
		printf("minishell: $%s: ambiguous redirect\n", exp->key);
		(*token)->content = key_not_found(&(*token)->content, amb->r,
				exp->len_key);
		return ;
	}
	(*token)->content = key_value(&(*token)->content, exp->value,
			amb->r, exp->len_key + 1);
}
