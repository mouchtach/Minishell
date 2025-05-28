/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouchtach <mouchtach@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:31:10 by ymouchta          #+#    #+#             */
/*   Updated: 2025/05/28 12:01:47 by mouchtach        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int	ft_lstsize_env(t_list *lst)
{
	t_list	*p;
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


void  add_back_env(t_list **list,  t_list *new)
{
    if(!list)
        return ;
    if(!(* list))
    {
        (* list) = new; 
        return;
    }
    t_list *tmp = * list;
    while(tmp->next)
        tmp = tmp->next;
    new->prev = tmp;
    tmp->next = new; 
}

t_list   *creat_new_env(char *value , char *key)
{
    t_list *new;

    new = NULL;
    new = malloc(sizeof(t_list));
    new->key = ft_strdup(key);
    new->value = ft_strdup(value);
    new->next = NULL;
    new->prev = NULL;
    return(new);
}

// t_env *set_env(t_list   *env)
// {
//     t_list *tmp;
    
//     t_env *list;
//     t_env *new;
//     list = NULL;
//     tmp = env;
//     while(tmp)
//     {
//         new = creat_new_env(tmp->value, tmp->key);
//         add_back_env(&list, new);
//         tmp = tmp->next;
//     }
//     return (list);
// }
