/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:52:00 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/05/28 17:52:25 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redir_char(char c)
{
	return (c == '>' || c == '<');
}

char	**tokenize_with_redirections(char *cmd_str)
{
	char	**tokens;
	char	*temp_cmd;
	int		i;
	int		j;

	temp_cmd = (char *)malloc(sizeof(char) * (ft_strlen(cmd_str) * 3 + 1));
	if (!temp_cmd)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd_str[i])
	{
		if (is_redir_char(cmd_str[i]))
		{
			if (i > 0 && cmd_str[i - 1] != ' ')
				temp_cmd[j++] = ' ';
			temp_cmd[j++] = cmd_str[i++];
			if (cmd_str[i] && is_redir_char(cmd_str[i])
				&& cmd_str[i] == cmd_str[i - 1])
				temp_cmd[j++] = cmd_str[i++];
			if (cmd_str[i] && cmd_str[i] != ' ')
				temp_cmd[j++] = ' ';
		}
		else
			temp_cmd[j++] = cmd_str[i++];
	}
	temp_cmd[j] = '\0';
	tokens = ft_split(temp_cmd, ' ');
	free(temp_cmd);
	return (tokens);
}

int	count_valid_tokens(char **tokens)
{
	int	i;
	int	count;
	int	redir_type;

	i = 0;
	count = 0;
	while (tokens[i])
	{
		redir_type = check_redirection_type(tokens[i]);
		if (redir_type == 0)
			count++;
		else if (tokens[i + 1])
			i++;
		i++;
	}
	return (count);
}

char	*build_cmd_string(char **tokens, int token_count)
{
	char	*new_cmd;
	char	*temp;
	int		i;

	if (token_count == 0)
		return (ft_strdup(""));
	new_cmd = ft_strdup("");
	if (!new_cmd)
		return (NULL);
	i = 0;
	while (tokens[i])
	{
		if (check_redirection_type(tokens[i]) > 0 && tokens[i + 1])
			i += 2;
		else
		{
			if (new_cmd[0] != '\0')
			{
				temp = ft_strjoin(new_cmd, " ");
				free(new_cmd);
				if (!temp)
					return (NULL);
				new_cmd = temp;
			}
			temp = ft_strjoin(new_cmd, tokens[i++]);
			free(new_cmd);
			if (!temp)
				return (NULL);
			new_cmd = temp;
		}
	}
	return (new_cmd);
}

int	add_redirections(char **tokens, t_redirec **redirec_list)
{
	int			i;
	int			redir_type;
	t_redirec	*new_node;

	i = 0;
	while (tokens[i])
	{
		redir_type = check_redirection_type(tokens[i]);
		if (redir_type > 0 && tokens[i + 1])
		{
			new_node = NULL;
			if (redir_type == 1)
				new_node = create_redirec_node(tokens[i + 1], D_OUTFILE);
			else if (redir_type == 2)
				new_node = create_redirec_node(tokens[i + 1], D_APPEND);
			else if (redir_type == 3)
				new_node = create_redirec_node(tokens[i + 1], D_INFILE);
			else if (redir_type == 4)
				new_node = create_redirec_node(tokens[i + 1], D_HERDOC);
			if (!new_node)
				return (1);
			add_redirec_node(redirec_list, new_node);
			i += 2;
		}
		else
			i++;
	}
	return (0);
}

char	*parse_redirections(char *cmd_str, t_redirec **redirec_list)
{
	char	**tokens;
	char	*new_cmd;
	int		token_count;

	tokens = tokenize_with_redirections(cmd_str);
	if (!tokens)
		return (NULL);
	token_count = count_valid_tokens(tokens);
	new_cmd = build_cmd_string(tokens, token_count);
	if (!new_cmd)
	{
		free_cmd_array(tokens);
		return (NULL);
	}
	if (add_redirections(tokens, redirec_list))
	{
		free(new_cmd);
		free_cmd_array(tokens);
		return (NULL);
	}
	free_cmd_array(tokens);
	return (new_cmd);
}

int	setup_cmd_struct_with_redirection(t_cmd *current, char *cmd_str)
{
	char *processed_cmd;

	if (!current || !cmd_str)
		return (1);
	current->redirec = NULL;
	processed_cmd = parse_redirections(cmd_str, &(current->redirec));
	if (!processed_cmd)
		return (1);
	current->cmd = ft_split(processed_cmd, ' ');
	free(processed_cmd);
	if (!current->cmd)
		return (1);
	return (0);
}