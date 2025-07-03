/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:09:31 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/06/21 15:47:18 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*assemble_command(char *input, t_list *env)
{
	t_cmd	*cmd;
	t_token	*tokens;

	tokens = NULL;
	if (!quotes_is_valid(input))
		return (first_free(tokens, input), printf(ERR_QUOTES), NULL);
	tokens = segment_input(input);
	if (!tokens)
		return (p1char(&input), NULL);
	refactor_tokens(&tokens, env);
	if (!all_scrap(tokens))
		return (first_free(tokens, input), NULL);
	cmd = create_list_cmd(tokens);
	if (!hydrate_cmd(&cmd, tokens))
		return (first_free(tokens, input), NULL);
	first_free(tokens, input);
	return (cmd);
}
