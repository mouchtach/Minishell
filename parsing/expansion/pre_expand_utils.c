/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_expand_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:00:00 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/07/30 16:50:38 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_pre_env_value(t_list *env, char *key)
{
	t_list	*current;
	int		key_len;

	current = env;
	key_len = ft_strlen(key);
	while (current)
	{
		if (current->key && ft_strlen(current->key) == key_len
			&& ft_strncmp(current->key, key, key_len) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*get_pre_expanded_value(char *var_name, t_shell *shell)
{
	char	*value;
	char	*quot_s;

	quot_s = NULL;
	if (!var_name)
		return (ft_strdup(""));
	value = get_pre_env_value(shell->env, var_name);
	quot_s = add_quotes(value);
	if (quot_s)
		return (quot_s);
	else if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

int	has_alpha_in_quoted_string(char *str)
{
	int	i;

	i = 1;
	while (i < ft_strlen(str) - 1)
	{
		if (ft_isalpha((unsigned char)str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	count_alpha_words_unquoted(char *str)
{
	int	i;
	int	count;
	int	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (str[i])
	{
		if ((unsigned char)str[i] != ' ')
		{
			if (!in_word)
			{
				in_word = 1;
				count++;
			}
		}
		else
			in_word = 0;
		i++;
	}
	return (count);
}

int	count_words_alpha_quoted(char *str)
{
	char	quote;

	if (!str || !*str)
		return (0);
	quote = is_fully_quoted(str);
	if (quote)
		return (has_alpha_in_quoted_string(str));
	return (count_alpha_words_unquoted(str));
}
