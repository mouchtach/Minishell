/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:50:09 by ymouchta          #+#    #+#             */
/*   Updated: 2025/05/21 15:49:36 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path_cmd(char **path, char *cmd)
{
	int		i;
	char	*join;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		join = ft_strjoin("/", cmd);
		tmp = ft_strdup(join);
		free(join);
		join = ft_strjoin(path[i], tmp);
		free(tmp);
		if (access(join, X_OK) == 0)
			return (join);
		i++;
	}
	free(join);
	printf("%s : command not found\n", cmd);
	return (NULL);
}

char **set_path(t_env *v)
{
    t_env *tmp;

    tmp = v;
    if(!tmp)
        return (NULL);
    while(ft_strcmp(tmp->key, "PATH"))
        tmp = tmp->next;
    return(ft_split(tmp->value, ":"));
}