/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:17:15 by abenajib          #+#    #+#             */
/*   Updated: 2025/05/25 09:45:28 by macbookpro       ###   ########.fr       */
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

//----colors
# define RED "\033[0;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"

//--macros
# define HEREDOC_FILE "/tmp/minishell_heredoc_tmp"
# define UNCLOSED "unexpected EOF while looking for matching quote"
# define EXIT_ERROR "exit: numeric argument required"
# define PIPE_ERROR "syntax error near unexpected token `|'\n"
# define SYNTAX_ERROR "syntax error near unexpected token `newline'\n"

extern int g_exit_status;
//--enums
typedef enum e_token_type
{
	WORD,
	PIPE,
	AND,
	OR,
	L_PARENTHESIS,
	R_PARENTHESIS,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}						t_token_type;



typedef struct s_token
{
	t_token_type		type;
	char				*value;
	bool				addspace;
	bool				variable;
	struct s_token		*current;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_lexer
{
	char				*input;
	int					pos;
	int					len;
}						t_lexer;

typedef struct s_redi_list
{
	t_token_type		type;
	char				*file;
	char				*content;
	bool				is_last;
	int					tmp_fd;
	bool				is_ambiguous;
	bool				expand;
	bool				variable;
	struct s_redi_list	*next;
}						t_redi_list;

typedef struct s_cmdarg
{
	char				**cmd;
	int					cmdsize;
	bool				is_builtin;
	int					origin_stdout;
	int					origin_stdin;
	t_redi_list			*input;
	t_redi_list			*output;
	struct s_cmdarg		*next;
}						t_cmdarg;

t_list					*ft_envinit(char **env);
int						ft_parse_env_var(char *env_var,
							char **key, char **value);
char					*ft_getcwd(t_list *env);
void					ft_init_token_fields(t_token *token);
t_token					*ft_handle_word(t_lexer *lexer);
t_token					*ft_handle_operator(t_lexer *lexer);

t_token					*ft_handle_quotes(t_lexer *lexer, char quote_char);
t_token					*ft_strtok(char *input);
t_lexer					*ft_lexer_init(char *input);
t_token					*ft_get_next_token(t_lexer *lexer);
t_token					*ft_newtok(t_token *token);
void					ft_freeee(char *temp2, char *exp);
t_cmdarg				*minishell(char *input, t_list **minienv);
int						ft_toksize(t_token *lst);
void					ft_tokadd_back(t_token **token_list, t_token *token);
void					ft_nodeadd_back(t_cmdarg **lst, t_cmdarg *new);
int						ft_isspecial(char c);
int						ft_isspace(char c);
bool					ft_is_duplicated(t_lexer *lexer, char op[3]);

void					ft_print_env(t_list *minienv);
void					ft_print_tokenlist(t_token *token_list);
char					*ft_printtype(t_token_type type);
void					ft_printredi(t_redi_list *redi);
void					ft_printcmd_list(t_cmdarg *cmdarg_list);

void					ft_free_tokenlist(t_token *token_list);
void					ft_free_token(t_token *token);
bool					ft_isredi(t_token *token);
bool					ft_is_cmd(t_token *current);
void					*ft_parse_word(t_cmdarg **node, t_token *token_list);
t_cmdarg				*ft_get_next_node(t_token *token_list);

t_cmdarg				*ft_newnode(t_cmdarg *node);
t_cmdarg				*ft_init_node(void);
void					ft_expand_variables(t_token **token, t_list *minienv);
void					ft_expand_var_in_char(char **value, t_list *minienv);
ssize_t					ft_dollar_pos(char *str);
int						ft_get_varlen(char *str);

char					*ft_getenv(char *var, t_list *minienv);
char					*ft_strjoin_free(char *s1, char *s2);
char					*ft_getvar(char *var, t_list *minienv);
void					ft_free_redi_list(t_redi_list *redi);
void					ft_rediradd(t_redi_list **redi, t_redi_list *new);

t_redi_list				*ft_redinew(t_token *token, bool expand);
void					ft_parse_redi(t_cmdarg **node, t_token *token_list);
void					ft_free_cmdlist(t_cmdarg *cmdarg_list);
void					ft_free_node(t_cmdarg *node);

bool					ft_condition(t_token **token, ssize_t dollar_pos);
char					*ft_expand(t_token **token, t_list *minienv,
							ssize_t dollar_pos);
char					*ft_temp2(t_token **token, ssize_t dollar_pos);
char					*ft_strjoin_free(char *s1, char *s2);

bool					ft_condition_inchar(char *value, ssize_t dollar_pos);
void					ft_expand_exit_status_inchar(char **value);
char					*ft_expand_inchar(char *value, t_list *minienv,
							ssize_t dollar_pos);
char					*ft_temp2_inchar(char *value, ssize_t dollar_pos);

// minishell_utils
bool					ft_redierrors(t_token *current);
bool					ft_pipeerrors(t_token *current);
void					ft_cleaner(t_token *token_list, t_cmdarg *cmdarg_list);


//EXECUTION

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef enum s_type
{
  D_IN,
  D_OUT,
  D_APPEND,
  D_HERDOC
}       t_type;

typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
}       t_env;

typedef struct s_redirec
{
    char    *name;
    t_type  type;
    struct s_redirec *next;
}       t_redirec;


typedef struct s_cmd
{
	char			**cmd;
	t_redirec		*redc;
	t_redirec		*input;
	t_redirec		*output;
	int				fd_herdoc[2];
	int				fd_io[2];
	int				fd_pip[2];
	struct s_cmd	*next;
	struct s_cmd	*prev;
}						t_cmd;

typedef struct s_exc
{
  t_cmd *list;
  t_env *env;
  char **path;
  int std_backup[2];

}   t_exc;


t_env	*set_env(char **env);
char	**set_path(t_env *v);
char	*get_path_cmd(char **path, char *cmd);
char	*get_next_line(int fd);
bool	ft_herdoc(t_exc *val);
t_exc   *strct_copy(t_cmdarg    *old_strct, char **env);
void    start_execution(t_exc *val);


//built_in
void    built_in_function(char **cmd);
#endif