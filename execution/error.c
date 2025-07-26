/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 22:04:33 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/26 16:36:20 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	file_error(int error_num, char *file_name, char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (error_num == -1)
	{
		ft_putstr_fd(file_name, 2);
		return (ft_putstr_fd(": ambiguous redirect\n", 2));
	}
	if (error_num == EACCES)
		return (perror(file_name));
	if (error_num == ENOENT)
		return (perror(file_name));
	if (error_num == EEXIST)
		return (perror(file_name));
	if (error_num == EISDIR)
		return (perror(file_name));
	if (error_num == ENOTDIR)
		return (perror(file_name));
}

void	error_message(int error_num, char *message, char *cmd)
{
	if (error_num == EACCES || error_num == ENOENT || error_num == EEXIST
		|| error_num == EISDIR || error_num == ENOTDIR || error_num == -1)
		return (file_error(error_num, message, cmd));
	else if (error_num == ENOMEM)
		return (perror("minishell"));
	else if (error_num == EINVAL)
		return (perror("minishell"));
	else if (error_num == ENOSPC)
		return (perror("minishell"));
	else if (error_num == EIO)
		return (perror("minishell"));
	else if (error_num == EPIPE)
		return (perror("minishell"));
	else if (error_num == EROFS)
		return (perror("minishell"));
	else if (error_num == ELOOP)
		return (perror("minishell"));
}
