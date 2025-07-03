/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:57:16 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/03 20:05:35 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void swap_nodes(t_list *node1, t_list *node2)
{
	if (!node1 || !node2)
		return;

	// Swap the key
	char *temp_key = node1->key;
	node1->key = node2->key;
	node2->key = temp_key;

	// Swap the value
	char *temp_value = node1->value;
	node1->value = node2->value;
	node2->value = temp_value;

	// Swap the eg flag
	bool temp_eg = node1->eg;
	node1->eg = node2->eg;
	node2->eg = temp_eg;
}

t_list *ft_copy_env(t_list *env)
{
	t_list *list;
	t_list *new = NULL;

	list = env;
	while(list)
	{
		add_back_env(&new, list_new_node(list->value, list->key, list->eg));
		list = list->next;
	}
	return(new);
}

int    add_export_list(t_list **env,char *value, char *key, bool eg)
{
	t_list *tmp;

	tmp = *env;
	while(tmp)
	{
		if(!ft_strcmp(tmp->key, key))
		{
			free(tmp->value);
			tmp->value = value;
			return (0);
		}
		tmp = tmp->next;
	}
	add_back_env(env, list_new_node(value, key , eg));
	return(1);

}

void    desplay_list_export(t_list *list)
{
	t_list *tmp;

	tmp = list;
	while(tmp)
	{
		if(tmp->eg == true)
			printf("%s='%s'\n", tmp->key, tmp->value);
		else
			printf("%s\n", tmp->key);
		tmp = tmp->next;
	}
}

void sort_export(t_list *var)
{
	t_list *new;
	t_list *tmp;
	t_list *tmp2;
	t_list *small;

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
	int i;
	bool eg;
	char *value;
	char *key;

	i = 0;
	eg = false;
	while(str[i] && str[i] != '=')
		i++;
	if(str[i] == '=')
	{
		value = ft_strdup(str + i + 1);
		eg = true;
	}
	else
		value = ft_strdup(str + i);
	key = ft_substr(str, 0, i);
	if(!add_export_list(&var->env, value, key, eg))
		free(value);
	else
	{
		free(value);
		free(key);
	}
}
void	ft_export_variable(t_shell *var, char **cmd)
{
	int		j;

	j = 1;
	if(!cmd[j])
		sort_export(var->env);
	while(cmd[j])
	{
		export_new(cmd[j], var);
		j++;
	}
}
