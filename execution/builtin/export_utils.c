/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 01:24:56 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/30 16:23:17 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_valid_export_key(const char *key)
{
	int	i;

	if (!key || !key[0])
		return (false);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (false);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

char	*get_valide_key(char *str)
{
	int		i;
	char	*key;

	if (!str || !str[0])
		return (NULL);
	if (str[0] != '_' && !ft_isalpha(str[0]))
		return (NULL);
	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (str[i] == '+' && str[i + 1] == '=')
		key = ft_substr(str, 0, i);
	else if (str[i] == '=' || str[i] == '\0')
		key = ft_substr(str, 0, i);
	else
		return (NULL);
	if (!key || key[0] == '\0')
		return (NULL);
	return (key);
}

void	desplay_list_export(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->eg == true)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else
			printf("%s\n", tmp->key);
		tmp = tmp->next;
	}
}

t_list	*ft_copy_env(t_list *env)
{
	t_list	*list;
	t_list	*new;

	new = NULL;
	list = env;
	while (list)
	{
		list_add_back(&new, list_new_node(list->value, list->key, list->eg));
		list = list->next;
	}
	return (new);
}

void	swap_nodes(t_list *node1, t_list *node2)
{
	char	*temp_key;
	char	*temp_value;
	bool	temp_eg;

	if (!node1 || !node2)
		return ;
	temp_key = node1->key;
	node1->key = node2->key;
	node2->key = temp_key;
	temp_value = node1->value;
	node1->value = node2->value;
	node2->value = temp_value;
	temp_eg = node1->eg;
	node1->eg = node2->eg;
	node2->eg = temp_eg;
}
