/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:55:20 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/03 20:06:44 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	desplay_env(char **env)
{
	int i = 0;

	if (!env)
		return ;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

void desplay(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->eg)
			printf("%s=%s\n", tmp->key, tmp->value);
		else
			printf("%s\n", tmp->key);
		tmp = tmp->next;
	}
}

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
void desplay_list(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->eg)
			printf("%s=%s\n", tmp->key, tmp->value);
		else
			printf("%s\n", tmp->key);
		tmp = tmp->next;
	}
}
int	main(int ac, char **av, char **ev)
{
	(void)ac;
	(void)av;
	char	*buffer;
	t_shell	*shell;
	
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
	// exit(g_exit_status);
}
