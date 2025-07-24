/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:19:39 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/23 12:05:35 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int		g_exit_status;

static void	clean_resources(t_shell *var, char *line)
{
	free_cmd_list(var->list);
	free(line);
}

void	handle_exit_on_eof(t_shell *var)
{
	rl_clear_history();
	free_list(&var->env);
	free(var);
	exit(0);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_shell	*var;

	var = malloc(sizeof(t_shell));
	(void)av;
	if (ac != 1)
		return (1);
	var->env = environment(env);
	g_exit_status = 0;
	while (1)
	{
		set_signals_main();
		var->list = NULL;
		line = readline("minishell> ");
		if (!line)
			handle_exit_on_eof(var);
		if (parse_input(line, var) != 0)
		{
			free(line);
			continue ;
		}
		execute_commands(var);
		clean_resources(var, line);
	}
}
