/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_d.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:02:28 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/07/27 13:50:42 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*process_split_result(char **split_tokens)
{
	char	*result;

	if (!split_tokens)
		return (NULL);
	if (split_tokens[0])
	{
		result = split_tokens[0];
		array_free(split_tokens);
		return (result);
	}
	else
	{
		free(split_tokens);
		return (NULL);
	}
}

char	*expand_single_token(char *token, t_shell *shell)
{
	char	*expanded;
	char	**split_tokens;

	expanded = expand_variables_in_token(token, shell);
	if (!expanded)
		return (NULL);
	split_tokens = quote_aware_split(expanded, ' ');
	free(expanded);
	return (process_split_result(split_tokens));
}
