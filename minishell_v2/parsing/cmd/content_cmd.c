/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:01:34 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/06 16:30:46 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	*others_node_red(t_redirec *new, t_redirec **tmp, t_token *tokens)
{
	new = red_node();
	new->type = tokens->type_token;
	new->name = ft_strdup(tokens->next->content);
	if (tokens->next->exp == 0)
		new->type = D_HERDOC_Q;
	(*tmp)->next = new;
	*tmp = new;
	return (new);
}

static t_redirec	*first_node(t_redirec *red, t_redirec **tmp,
		t_token *tokens, int *i)
{
	red = red_node();
	red->type = tokens->type_token;
	red->name = ft_strdup(tokens->next->content);
	if (tokens->next->exp == 0)
		red->type = D_HERDOC_Q;
	*tmp = red;
	*i = *i + 1;
	return (red);
}

static void	norm(t_cm *var, t_redirec **v4, t_token **tokens)
{
	if ((*tokens)->type_token == PIPE)
		*tokens = (*tokens)->next;
	var->r = 0;
	var->i = 0;
	var->size = analyze_word(*tokens);
	*v4 = NULL;
}

static bool	control_cmd(t_cm1 *l_var, t_redirec **tmd, t_token **tokens, int *i)
{
	if (!(*tokens)->next)
		return (printf(ERR_RED), 0);
	if (!*i)
		*tmd = first_node(*tmd, &l_var->tmp_red, *tokens, i);
	else
		others_node_red(l_var->new_red, &l_var->tmp_red, *tokens);
	*tokens = (*tokens)->next;
	return (1);
}

bool	hydrate_cmd(t_cmd **cmd, t_token *tokens)
{
	t_cmd	*tmd;
	t_cm1	l_var;
	t_cm	var;

	tmd = *cmd;
	l_var.new_red = NULL;
	while (tmd)
	{
		norm(&var, &l_var.tmp_red, &tokens);
		if (!mvalloc(&tmd->cmd, var.size))
			return (0);
		while (tokens && tokens->type_token != PIPE)
		{
			if (tokens->type_token == WORD)
				tmd->cmd[var.r++] = ft_strdup(tokens->content);
			else if (tokens->type_token != WORD)
				if (!control_cmd(&l_var, &tmd->redirec, &tokens, &var.i))
					return (0);
			amb_next(tokens, tmd);
			tokens = tokens->next;
		}
		tmd->cmd[var.r] = NULL;
		tmd = tmd->next;
	}
	return (1);
}
