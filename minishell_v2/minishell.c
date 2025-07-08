/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:19:39 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/08 17:51:50 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	exit_status;


char	*rd_line(t_list *env)
{
	char	*rd_line;

	rd_line = NULL;
	rd_line = readline("minishell-$> ");
	if (!rd_line)
	{
		env_leaks(env);
		printf("\033[1A");
		printf("\033[13C");
		printf("exit\n");
		exit(0);
	}
	history_input(rd_line);
	return (rd_line);
}

int	main(int ac, char **av, char **ev)
{
	char	*buffer;
	t_shell	*shell;

	(void)ac;
	(void)av;
	// signal(SIGINT, handle_sigint);
	shell = malloc(sizeof(t_shell));
	exit_status = 0;
	shell->env = environment(ev);
	while (1)
	{
		set_signals_main();
		buffer = rd_line(shell->env);
		shell->list = assemble_command(buffer, shell->env);
		if (!shell->list)
			continue ;
		execute_commands(shell);
		cmdfree(shell->list);
	}
}
