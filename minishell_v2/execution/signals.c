/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 12:36:03 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/04 22:16:52 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	restore_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_parent_heredoc_sigint(int sig)
{
	(void)sig;
}

void	herdoc_sig(void)
{
	signal(SIGINT, handle_parent_heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
}

/*
 * To prevent "^C" from being displayed, make sure to use
 * sigaction with the SA_RESTART flag and do NOT set the
 * terminal to echo control characters (ECHOCTL).
 *
 * In your main function or initialization code, add:
 *
 * struct termios term;
 * tcgetattr(STDIN_FILENO, &term);
 * term.c_lflag &= ~ECHOCTL;
 * tcsetattr(STDIN_FILENO, TCSANOW, &term);
 *
 * This disables echoing "^C" when Ctrl+C is pressed.
 */
