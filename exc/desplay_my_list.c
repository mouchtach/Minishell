/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   desplay_my_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:52:20 by ymouchta          #+#    #+#             */
/*   Updated: 2025/05/16 10:03:31 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <string.h>

// Tree-drawing characters
#define TREE_VERT    "│"
#define TREE_BRANCH  "├─"
#define TREE_END     "└─"
#define TREE_INDENT  "   "

// Colors
#define COLOR_CMD    "\033[1;33m"  // Yellow
#define COLOR_IN     "\033[0;36m"  // Cyan
#define COLOR_OUT    "\033[0;32m"  // Green
#define COLOR_FD     "\033[0;35m"  // Magenta
#define COLOR_RESET  "\033[0m"

const char* get_type_name(t_type type) {
    switch(type) {
        case D_IN:    return "INPUT";
        case D_OUT:   return "OUTPUT";
        case D_APPEND: return "APPEND";
        case D_HERDOC: return "HEREDOC";
        default:      return "UNKNOWN";
    }
}

void print_redirection_tree(t_redirec *list, const char *prefix, const char *color) {
    while(list) {
        char next_prefix[32];
        strcpy(next_prefix, prefix);
        strcat(next_prefix, (list->next ? TREE_VERT TREE_INDENT : "  " TREE_INDENT));

        printf("%s%s%s %s%-8s%s → '%s'\n",
               prefix,
               (list->next ? TREE_BRANCH : TREE_END),
               color,
               COLOR_CMD, get_type_name(list->type),
               color,
               list->name);

        list = list->next;
    }
}

void print_command_tree(t_cmd *cmd, int cmd_num) {
    // Command header
    printf("%sCommand #%d%s\n", COLOR_CMD, cmd_num, COLOR_RESET);

    // Main command
    printf("%s %sCommand:%s ", TREE_BRANCH, COLOR_CMD, COLOR_RESET);
    if (cmd->cmd && cmd->cmd[0]) {
        for (int i = 0; cmd->cmd[i]; i++) {
            printf("%s%s", i > 0 ? " " : "", cmd->cmd[i]);
        }
    } else {
        printf("(empty)");
    }
    printf("\n");

    // Input redirections
    printf("%s %sInput Redirections%s\n",
           TREE_BRANCH, COLOR_IN, COLOR_RESET);
    print_redirection_tree(cmd->input, TREE_VERT TREE_INDENT, COLOR_IN);

    // Output redirections
    printf("%s %sOutput Redirections%s\n",
           TREE_BRANCH, COLOR_OUT, COLOR_RESET);
    print_redirection_tree(cmd->output, TREE_VERT TREE_INDENT, COLOR_OUT);

    // File descriptors
    printf("%s %sFile Descriptors%s\n",
           TREE_END, COLOR_FD, COLOR_RESET);
    printf("%s   %sfiles:%s %d,%d\n",
           TREE_INDENT, COLOR_FD, COLOR_RESET,
           cmd->fd_files[0], cmd->fd_files[1]);
    printf("%s   %spipe:%s %d,%d\n",
           TREE_INDENT, COLOR_FD, COLOR_RESET,
           cmd->fd_pip[0], cmd->fd_pip[1]);
    printf("%s   %soriginal:%s %d,%d\n",
           TREE_INDENT, COLOR_FD, COLOR_RESET,
           cmd->fd_origine[0], cmd->fd_origine[1]);
}