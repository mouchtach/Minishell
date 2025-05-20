/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:14:53 by abenajib          #+#    #+#             */
/*   Updated: 2025/05/20 15:26:38 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_exit_status = 0;

int	ft_toksize(t_token *lst)
{
	t_token	*p;
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

int	ft_check_syntax(t_token *token_list)
{
	t_token	*current;

	current = token_list;
	if (ft_toksize(token_list) == 1 && ft_isredi(current))
		return (printf(RED SYNTAX_ERROR RESET), g_exit_status = 2, -1);
	while (current)
	{
		if (ft_pipeerrors(current))
			return (printf(RED PIPE_ERROR RESET), g_exit_status = 2, -1);
		if (ft_redierrors(current))
			return (printf(RED SYNTAX_ERROR RESET), g_exit_status = 2, -1);
		current = current->next;
	}
	return (0);
}

t_cmdarg	*ft_parser(t_token *token_list, t_list *minienv)
{
	t_cmdarg	*cmdarg_list;
	t_cmdarg	*node;
	t_token		*tmp;

	if (!token_list)
		return (NULL);
	cmdarg_list = NULL;
	tmp = token_list;
	while (tmp)
	{
		if (!(tmp->type == WORD && tmp->prev && tmp->prev->type == HEREDOC))
			ft_expand_variables(&tmp, minienv);
		tmp = tmp->next;
	}
	token_list->current = token_list;
	node = ft_get_next_node(token_list);
	while (node)
	{
		if (node)
			ft_nodeadd_back(&cmdarg_list, ft_newnode(node));
		freeall(node->cmd, node->cmdsize);
		free(node);
		node = ft_get_next_node(token_list);
	}
	return (cmdarg_list);
}

t_cmdarg	*minishell(char *input, t_list **minienv)
{
	t_token		*token_list;
	t_cmdarg	*cmdarg_list;

	if (input == NULL)
	{
		printf(RED "[EOF]\n" RESET);
		exit(0);
	}
	if (input[0] == '\0')
		return (NULL);
	add_history(input);
	token_list = ft_strtok(input);
	if (ft_check_syntax(token_list) == -1)
		return (NULL);
	cmdarg_list = ft_parser(token_list, *minienv);
	// ft_printcmd_list(cmdarg_list);
	return(cmdarg_list);
	// // exec
	// ft_cleaner(token_list, cmdarg_list);
}

int	main(int ac, char **av, char **env)
{
	t_list	*minienv;
	t_cmdarg	*ot;
	char	*input;
	char	*cwd;
	t_exc	*var_exc;

	(void)av;
	if (ac != 1)
		return (printf(YELLOW "\nError: No arguments expected\n" RESET), 1);
	else
	{
		minienv = ft_envinit(env);
		while (1)
		{
			cwd = ft_getcwd(minienv);
			input = readline(cwd);
			ot =  minishell(input, &minienv);
			// htal hna khdit ghir parssing
			var_exc = strct_copy(ot, env);
			// print_command_tree();
			start_execution(var_exc);

			//
			free(input);
			free(cwd);
		}
	}
	return (0);
}


