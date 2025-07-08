/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_scrap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 13:54:17 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/06 17:14:07 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	wr_syntax(t_type type)
{
	char	*red;

	if (type == D_HERDOC)
		red = "<<";
	if (type == D_APPEND)
		red = ">>";
	if (type == D_INFILE)
		red = "<";
	if (type == D_OUTFILE)
		red = ">";
	printf("minishell: syntax error near unexpected token `%s'\n", red);
}

void	is_vred(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type_token != WORD && tokens->type_token != PIPE
			&& tokens->type_token != ENV)
			tokens->red = 1;
		tokens = tokens->next;
	}
}
