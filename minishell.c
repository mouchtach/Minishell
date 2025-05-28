/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:51:02 by ymouchta          #+#    #+#             */
/*   Updated: 2025/05/28 20:55:37 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_list(t_cmd *token)
{
	t_cmd	*next;

	while (token)
	{
		next = token->next;
		free_cmd_node(token);
		token = next;
	}
}

int	process_line(char *line, t_cmd **token_ptr)
{
	if (ft_strlen(line) <= 0)
		return (0);
	add_history(line);
	*token_ptr = tokenization(line);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_shell	*var = malloc(sizeof(t_shell));

	(void)av;
	if (ac != 1)
		return (1);
    // set_env();
    var->env =  set_env(env);
    var->path = set_path(var->env);
	while (1)
	{
		var->list = NULL;
		line = readline("minishell> ");
		if (process_line(line, &var->list) != 0)
			return (1);
		if (syntax_error(line))
			free_cmd_list(var->list);
		else if (var->list)
		{
			print_cmd_list(var->list);
            start_execution(var);
            // built_in_function(var->list->cmd,  var);
			free_cmd_list(var->list);
            
		}
		else
			free(line);
	}
}

