/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:50:09 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/03 14:18:06 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_executable_paths(char **path, char *cmd)
{
	int		i;
	char	*join;
	char	*tmp;

	i = 0;
	if(path)
	{
		while (path[i])
		{
			join = ft_strjoin("/", cmd);  //   /ls
			tmp = ft_strdup(join);  //  /bin
			free(join);
			join = ft_strjoin(path[i], tmp);
			free(tmp);
			if (access(join, X_OK) == 0)
				return (join);
			i++;
		}
		free(join);
	}
	// ft_putstr_fd();
	printf("%s : command not found\n", cmd);
	return (NULL);
}

char **get_system_paths(t_list *v)
{

    char *value = get_value(v, "PATH");
	if (!value)
		return (NULL);
    return(ft_split(value, ':')); // ""
}