/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:19:39 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/03 22:21:42 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

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
	glance_input(rd_line, env);
	return (rd_line);
}

int	main(int ac, char **av, char **ev)
{
	char	*buffer;
	t_shell	*shell;

	(void)ac;
	(void)av;
	shell = malloc(sizeof(t_shell));
	g_exit_status = 0;
	shell->env = environment(ev);
	while (1)
	{
		buffer = rd_line(shell->env);
		shell->list = assemble_command(buffer, shell->env);
		if (!shell->list)
			continue ;
		execute_commands(shell);
		cmdfree(shell->list);
	}
	free_list(&shell->env);
	free(shell);
}
