/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:19:12 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/08 23:27:21 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "./parsing/include/syntax.h"
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/history.h>
# include <readline/readline.h>

# define OPEN_FAILD "minishell open faild"
# define DUP_FAILD "minishell dup faild"
# define HERDOC_FAILD "minishell herdoc"
# define JOIN_FAILD "minishell join faild"
# define FORK_FAILD "minishell fork faild"
# define GET_LINE "minishell get next line faild"
# define ERR_MEM "minishell alloc"

extern int				exit_status;
typedef enum s_type
{
	WORD,
	PIPE,
	ENV,
	D_OUTFILE,
	D_APPEND,
	D_INFILE,
	D_HERDOC,
	D_HERDOC_Q
}						t_type;

typedef struct s_amb
{
	bool	d_quotes;
	bool	s_quotes;
	bool	ambiguous;
	int		r;
}			t_ambg;

typedef struct s_token
{
	char				*content;
	bool				red;
	bool				exp;
	bool				amb;
	t_type				type_token;
	struct s_token		*next;
}						t_token;

typedef struct s_redirec
{
	char				*name; // $v
	t_type				type; // AMG
	struct s_redirec	*next;
}						t_redirec;

typedef struct s_cmd
{
	char				**cmd; //
	bool				amb;
	t_redirec			*redirec; //
	int					fd_herdoc[2];
	int					fd_io[2];
	int					fd_pip[2];
	struct s_cmd		*next;
	struct s_cmd		*prev;
}						t_cmd;

typedef struct s_shell
{
	t_cmd				*list; //
	t_list				*env; //
	int					std_backup[2];
	int					exit_status;
}						t_shell; //

typedef struct s_spl
{
	int					i;
	int					r;
	bool				f_quotes;
	char				*new_token;
}						t_spl;

typedef struct s_refactor
{
	char				*new;
	char				quotes;
	int					r;
	int					f;
	bool				flag;
}						t_refactor;

typedef struct s_exp
{
	int					r;
	int					len_key;
	int					len_value;
	char				*value;
	char				*key;
}						t_exp;

typedef struct s_norm
{
	int					r;
	int					pipe;
}						t_norm;

typedef struct s_cm
{
	int					size;
	int					r;
	int					i;
}						t_cm;

typedef struct s_cm1
{
	t_redirec			*new_red;
	t_redirec			*tmp_red;
}						t_cm1;

/*~~~~~~~~~~~~~~~~~~~~~~~<history.c>~~~~~~~~~~~~~~~~~~~~~~~*/
void					history_input(char *input);
/*~~~~~~~~~~~~~~~~~~~~~~~<token.c>~~~~~~~~~~~~~~~~~~~~~~~*/
t_cmd					*assemble_command(char *input, t_list *env);
/*~~~~~~~~~~~~~~~~~~~~<list_tokens.c>~~~~~~~~~~~~~~~~~~~~~*/
t_token					*segment_input(char *tokens);
/*~~~~~~~~~~~~~~~~~~<refactor_tokens.c>~~~~~~~~~~~~~~~~~~~*/
void					refactor_tokens(t_token **tokens, t_list *env);
/*~~~~~~~~~~~~~~~~~~~~~~<unquotes.c>~~~~~~~~~~~~~~~~~~~~~~*/
bool					has_quotes(char *str);
char					*remove_quotes(char *str);
/*~~~~~~~~~~~~~~~~~~~~<utils0_tokens.c>~~~~~~~~~~~~~~~~~~*/
int						skip_space(char *str);
int						add_value(int r, bool *f_quotes);
void					set_var_zero(int *v1, int *v2, bool *v3, t_token **lv4);
void					node_back(t_token **main, t_token *new);
t_token					*create_node(char *content);
/*~~~~~~~~~~~~~~~~~~~~<utils1_tokens.c>~~~~~~~~~~~~~~~~~~*/
bool					has_env(char *content);
bool					is_symbols(char c);
bool					is_space(char c);
bool					quotes_is_valid(char *tokens);
/*~~~~~~~~~~~~~~~~~~~~<utils3_tokens.c>~~~~~~~~~~~~~~~~~~*/
void					cut_value_quotes(int *r, char *tokens, char c,
							bool flag);
/*~~~~~~~~~~~~~~~~~~~~~<env_expander.c>~~~~~~~~~~~~~~~~~~~*/
void					is_env(t_token **token, t_list *env, bool expander,
							bool ambg);
char					*key_value(char **content, char *v_env, int pos,
							int len_key);
char					*key_not_found(char **content, int pos_key,
							int len_key);
char					*env_value(char *key, t_list *env);
/*~~~~~~~~~~~~~~~~~~~~~<env_heredoc.c>~~~~~~~~~~~~~~~~~~~*/
void					resolve_heredoc(t_list *env, char **input, int fd);
/*~~~~~~~~~~~~~~~~~~~~~~<env_list.c>~~~~~~~~~~~~~~~~~~~~~~*/
t_list					*construct_env(char **env);
/*~~~~~~~~~~~~~~~~~~~~~~<env_split.c>~~~~~~~~~~~~~~~~~~~~~~*/
void					env_space(char **input, t_list *env);
/*~~~~~~~~~~~~~~~~~~~~~~<exp_special.c>~~~~~~~~~~~~~~~~~~~~~~*/
void					ambiguous_redirect(t_token **token, bool amb,
							char *key);
bool					is_special(char c, bool f_quotes);
int						count_word(char *content);
int						expand_meta(char **content, int pos, int r,
							bool f_quotes);
/*~~~~~~~~~~~~~~~~~~~~~~<utils_env.c>~~~~~~~~~~~~~~~~~~~~~~*/
void					change_value(bool *quotes, int value);
void					increment(int *v1, int *v2);
void					set_var_exp(int *v1, int *v2, int *v3, int v4);
char					*cdup(int size, char *content);
bool					is_valid_key(char c);
/*~~~~~~~~~~~~~~~~~~~~~~<utils_env.c>~~~~~~~~~~~~~~~~~~~~~~*/
void					set_new_content(t_token **token, t_exp *exp,
							t_ambg *amb);
/*~~~~~~~~~~~~~~~~~~~~~~<env_leaks.c>~~~~~~~~~~~~~~~~~~~~~~*/
void					env_leaks(t_list *env);
/*~~~~~~~~~~~~~~~~~~~~~~<list_cmd.c>~~~~~~~~~~~~~~~~~~~~~~*/
t_cmd					*create_list_cmd(t_token *tokens);
/*~~~~~~~~~~~~~~~~~~~~~~<utils_cmd.c>~~~~~~~~~~~~~~~~~~~~~~*/
int						counter_pipe(t_token *tokens);
int						analyze_word(t_token *tokens);
bool					mvalloc(char ***commands, int size);
void					amb_next(t_token *token, t_cmd *tmd);
/*~~~~~~~~~~~~~~~~~~~~~~<nodes_cmd.c>~~~~~~~~~~~~~~~~~~~~~~*/
t_cmd					*cmd_node(void);
t_redirec				*red_node(void);
/*~~~~~~~~~~~~~~~~~~~~~~<content_cmd.c>~~~~~~~~~~~~~~~~~~~~~~*/
bool					hydrate_cmd(t_cmd **cmd, t_token *tokens);
/*~~~~~~~~~~~~~~~~~~~~~~<scrap.c>~~~~~~~~~~~~~~~~~~~~~~*/
bool					all_scrap(t_token *tokens);
/*~~~~~~~~~~~~~~~~~~~~~~<utils_scrap.c>~~~~~~~~~~~~~~~~~~~~~~*/
void					is_vred(t_token *tokens);
void					wr_syntax(t_type type);
/*~~~~~~~~~~~~~~~~~~~~~~<leaks.c>~~~~~~~~~~~~~~~~~~~~~~*/
void					first_free(t_token *tokens, char *input);
void					p1char(char **ptr);
void					p2char(char ***ptr);
/*~~~~~~~~~~~~~~~~~~~~~~<leaks.c>~~~~~~~~~~~~~~~~~~~~~~*/
void					cmdfree(t_cmd *cmd);

// void						set_signals_main(void);
// void						set_signals_child(void);
// int						exit_status(int val);
// int						control_g(bool option, bool value);

// EXECUTION

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

// t_list
char					**get_system_paths(t_list *v);
char					*get_executable_paths(char **path, char *cmd);
char					*get_next_line(int fd);
bool					process_heredocs(t_shell *val);
void					execute_commands(t_shell *val);
// redirections
bool					set_input(t_cmd *command, t_redirec *in);
bool					set_output(t_cmd *command, t_redirec *out);
bool					handle_redirections(t_cmd *command);
bool					setup_pipes(t_cmd *command);
bool					duplicate_standard_fds(t_cmd *cmd);
// unset
int						ft_unset(t_shell *val, char **cmd);
// std
bool					init_shell_fds(t_shell *shell);
void					cleanup_shell_fds(t_shell *shell);
bool					restore_standard_input(t_shell *shell);
// fork
void					child_process(t_shell *val, t_cmd *cmd);
void					parent_process(t_cmd *cmd);
void					execute_with_fork(t_shell *val);
// built_in
void					execute_builtin(char **cmd, t_shell *val);
int						is_builtin(char *cmd);
int						ft_exit(char **cmd, t_shell **shell);
//	//export
void					add_export_list(t_list **env, char *value, char *key,
							bool eg);
void					sort_export(t_list *var);
int						export_new(char *str, t_shell *var);
int						ft_export_variable(t_shell *var, char **cmd);
//	//export_utils
char					*get_valide_key(char *str);
t_list					*ft_copy_env(t_list *env);
void					swap_nodes(t_list *node1, t_list *node2);
void					desplay_list_export(t_list *list);
//	//cd
char					*resolve_cd_path(char *str, t_list *env);
void					update_env(char *key, char *value, t_list **env);
int						ft_cd(t_list *env, char *path);
char					*get_value(t_list *env, char *key);
//	//echo
int						ft_echo(char **cmd);
// error
void					error_message(int error_num, char *message);
// list_utils
int						list_size(t_list *list);
void					list_add_back(t_list **list, t_list *new);
t_list					*list_new_node(char *value, char *key, bool eg);
// environment_utils
void					add_default_env(t_list **list);
char					*add_shlvl(char *value);
char					**build_environment_array(t_list *list);
// environment
void					set_value_key(char *line, char **key, char **value);
t_list					*check_and_create_env_node(char *key, char *value);
t_list					*set_env(char **env);
t_list					*environment(char **env);
// leaks meme
void					free_list_node(t_list *node);
void					free_list(t_list **node);
void					cleanup_shell(t_shell **shell);
// leaks fd
void					clear_all_pipes(t_cmd *cmd);
void					close_fd(int *fd);
void					initialize_command_fds(t_cmd *cmd);
//signals
void					set_signals_child(void);
void					signal_herdoc(int sig);
void					set_signals_main(void);
//exit status
bool					wait_and_exit(int pid);
#endif
