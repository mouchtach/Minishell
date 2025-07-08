/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refactor_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:10:51 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/06 16:43:56 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	demote_env_token(t_token **tokens)
{
	t_token	*token;

	token = *tokens;
	while (token)
	{
		if (token->type_token == ENV)
			token->type_token = WORD;
		token = token->next;
	}
}

static bool	is_ambiguous(t_token *token)
{
	if (token->type_token == D_INFILE || token->type_token == D_OUTFILE
		|| token->type_token == D_APPEND)
		return (1);
	return (0);
}

void	refactor_tokens(t_token **tokens, t_list *env)
{
	t_token	*token;
	bool	expander;
	bool	ambg;

	token = *tokens;
	expander = 1;
	ambg = 0;
	while (token)
	{
		is_env(&token, env, expander, ambg);
		if (has_quotes(token->content))
		{
			if (!expander)
				token->exp = 0;
			token->content = remove_quotes(token->content);
		}
		expander = 1;
		if (token->type_token == D_HERDOC)
			expander = 0;
		ambg = is_ambiguous(token);
		token = token->next;
	}
	demote_env_token(tokens);
}
