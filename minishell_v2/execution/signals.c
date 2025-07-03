/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 12:36:03 by ymouchta          #+#    #+#             */
/*   Updated: 2025/06/29 15:43:05 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	handle_sigint(int sig)
// {
// 	(void)sig;
// 	write(1, "\n", 1);
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// 	g_exit_status = 1;
// }
// void	handle_parent_sigint(int sig)
// {
// 	(void)sig;
// 	g_exit_status = 130;
// }
// void	handle_parent_heredoc_sigint(int sig)
// {
// 	(void)sig;
// 	write(1, "\n", 1);
// 	g_exit_status = 1;
// }

// void	handle_heredoc_sigint(int sig)
// {
// 	(void)sig;
// 	exit(1);
// }

// void	handle_signals(void)
// {
// 	signal(SIGINT, handle_sigint);
// 	signal(SIGQUIT, SIG_IGN);
// }
