/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_std.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 21:49:58 by ymouchta          #+#    #+#             */
/*   Updated: 2025/06/20 21:50:22 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool  init_shell_fds(t_shell *shell)
{
    shell->std_backup[0] = dup(STDIN_FILENO);   // Backup stdin
    shell->std_backup[1] = dup(STDOUT_FILENO);  // Backup stdout
    if (shell->std_backup[0] == -1 || shell->std_backup[1] == -1)
        return (perror(DUP_FAILD), false);
    return (true);
}

void cleanup_shell_fds(t_shell *shell)
{
    close(shell->std_backup[0]);
    close(shell->std_backup[1]);
}

void reset_stdin(t_shell *shell)
{
    if (dup2(shell->std_backup[0], STDIN_FILENO) == -1)
        perror("minishell: stdin reset failed");
    if (dup2(shell->std_backup[1], STDOUT_FILENO) == -1)
        perror("minishell: stdout reset failed");
}