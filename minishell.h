/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:51:10 by ymouchta          #+#    #+#             */
/*   Updated: 2025/06/19 15:04:38 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <curses.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "libft/libft.h"

# define COLORE_RESET "\033[0m"
# define COLORE_RED "\033[1;31m"
# define COLORE_GREEN "\033[1;32m"
# define COLORE_YELLOW "\033[1;33m"
# define COLORE_BLUE "\033[1;34m"
# define COLORE_MAGENTA "\033[1;35m"
# define COLORE_CYAN "\033[1;36m"
# define COLORE_WHITE "\033[1;37m"

typedef enum s_type
{
	D_OUTFILE,
	D_APPEND,
	D_INFILE,
	D_HERDOC
}						t_type;

typedef struct s_redirec
{
	char				*name;
	t_type				type;
	struct s_redirec	*next;
}						t_redirec;

typedef struct s_cmd
{
	char			**cmd;
	t_redirec		*redirec;
	int				fd_herdoc[2];
	int				fd_io[2];
	int				fd_pip[2];
	struct s_cmd	*next;
	struct s_cmd	*prev;
}						t_cmd;


typedef struct s_shell
{
  t_cmd *list;
  t_list *env;
  char **path;
  int std_backup[2];
}   t_shell;

/*syntax_error.c*/

int						syntax_error(char *line);

/* utils_a.c */
int						free_cmd_array(char **cmds);
int						allocate_token(t_cmd **token, char **cmds);
int						setup_cmd_struct(t_cmd *current, char *cmd_str);
int						create_next_node(t_cmd *current, int has_next);

/* utils_b.c */
int						arg_create(t_cmd *token, char **cmds);
t_cmd					*handle_token_error(char **cmds, t_cmd *token);
t_cmd					*tokenization(char *line);
void					print_cmd_list(t_cmd *token);
void					free_cmd_node(t_cmd *node);

/* main.c */
void					free_cmd_list(t_cmd *token);
int						process_line(char *line, t_cmd **token_ptr);

/* redirection.c */
t_redirec				*create_redirec_node(char *name, t_type type);
void					add_redirec_node(t_redirec **head, t_redirec *new);
void					free_redirec_list(t_redirec *head);
int						check_redirection_type(const char *str);
void					print_redirec_list(t_redirec *head);
char					**tokenize_with_redirections(char *cmd_str);

/* parse_redir.c */
int						count_valid_tokens(char **tokens);
char					*build_cmd_string(char **tokens, int token_count);
int						add_redirections(char **tokens,
							t_redirec **redirec_list);
char					*parse_redirections(char *cmd_str,
							t_redirec **redirec_list);
int						setup_cmd_struct_with_redirection(t_cmd *current,
							char *cmd_str);
int						is_redir_char(char c);

/* doubly_linked_utils.c */
t_cmd					*get_first_cmd(t_cmd *node);


//EXECUTION

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

// t_list	*set_list(t_list *env);
char	**set_path(t_list *v);
char	*get_path_cmd(char **path, char *cmd);
char	*get_next_line(int fd);
bool	ft_herdoc(t_shell *val);
// t_shell   *strct_copy(t_cmdarg    *old_strct, t_list *env);
void    start_execution(t_shell *val);


//built_in
void    built_in_function(char **cmd, t_shell *var);
int		is_built(char *cmd);
t_list  *set_env(char **env);
t_list  *creat_new_env(char *value , char *key, bool eg);
void    add_back_env(t_list **list,  t_list *new);
// t_list   *creat_new_env(char *value , char *key);

#endif