/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:31:10 by ymouchta          #+#    #+#             */
/*   Updated: 2025/05/26 20:47:43 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int	ft_lstsize_env(t_env *lst)
{
	t_env	*p;
	int		len;

	if (lst == NULL)
		return (0);
	p = lst;
	len = 0;
	while (p != NULL)
	{
		p = p->next;
		len++;
	}
	return (len);
}


void  add_back_env(t_env **list,  t_env *new)
{
    if(!list)
        return ;
    if(!(* list ))
    {
        (* list) = new; 
        return;
    }
    t_env *tmp = * list;
    while(tmp->next)
        tmp = tmp->next;
    tmp->next = new; 
}

t_env   *creat_new_env(char *value , char *key)
{
    t_env *new;

    new = NULL;
    new = malloc(sizeof(t_env));
    new->key = ft_strdup(key);
    new->value = ft_strdup(value);
    new->next = NULL;
    return(new);
}

t_env *set_env(char **env)
{
    t_env *v = NULL;
    int j;
    int i;
    char *value;
    char *key;

    i = 0;
    while(env[i])
    {
        j = 0;
        while(env[i][j] != '=')
            j++;
        value = ft_substr(env[i], j + 1 , ft_strlen(env[i]) - j);
        key = ft_substr(env[i], 0, j);
        add_back_env(&v, creat_new_env(value, key));
        free(value);
        free(key);
        i++;
    }
    return(v);
}
