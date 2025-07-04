/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:57:16 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/04 01:25:59 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	add_export_list(t_list **env, char *value, char *key, bool eg)
{
	t_list	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			free(tmp->value);
			tmp->value = value;
			return (0);
		}
		tmp = tmp->next;
	}
	list_add_back(env, list_new_node(value, key, eg));
	return (1);
}

void	sort_export(t_list *var)
{
	t_list	*new;
	t_list	*tmp;
	t_list	*tmp2;
	t_list	*small;

	new = NULL;
	new = ft_copy_env(var);
	tmp = new;
	while (tmp)
	{
		small = tmp;
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp2->key, small->key) < 0)
				small = tmp2;
			tmp2 = tmp2->next;
		}
		if (small != tmp)
			swap_nodes(small, tmp);
		tmp = tmp->next;
	}
	desplay_list_export(new);
	free_list(&new);
}

void	export_new(char *str, t_shell *var)
{
	int		i;
	bool	eg;
	char	*value;
	char	*key;

	i = 0;
	eg = false;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
	{
		value = ft_strdup(str + i + 1);
		eg = true;
	}
	else
		value = ft_strdup(str + i);
	key = ft_substr(str, 0, i);
	if (!add_export_list(&var->env, value, key, eg))
		free(value);
	else
	{
		free(value);
		free(key);
	}
}

void	ft_export_variable(t_shell *var, char **cmd)
{
	int	j;

	j = 1;
	if (!cmd[j])
		sort_export(var->env);
	while (cmd[j])
	{
		export_new(cmd[j], var);
		j++;
	}
}
