NAME	= minishell

CC		= cc

READLINE_DIR = $(shell brew --prefix readline)

CFLAGS	= -Wall -Wextra -Werror -I$(READLINE_DIR)/include

LDFLAGS	= -L$(READLINE_DIR)/lib

RFLG	= -lreadline -lncurses

LIB		= ./libft/libft.a

# Source files
SRC =	minishell.c									\
		parsing/h_exp.c								\
		parsing/h_exp_utils.c						\
		parsing/parsing.c							\
		parsing/init_structs.c						\
		parsing/cleanup.c							\
		parsing/redirecting/parse_redir.c 			\
		parsing/redirecting/parse_redir_utils.c		\
		parsing/redirecting/parse_redir_utils_b.c 	\
		parsing/redirecting/redirection.c 			\
		parsing/utils/utils_a.c 					\
		parsing/utils/utils_b.c 					\
		parsing/utils/utils_c.c 					\
		parsing/expansion/pre_expand.c				\
		parsing/expansion/expansion.c 				\
		parsing/expansion/expansion_utils.c			\
		parsing/expansion/expansion_utils_b.c		\
		parsing/expansion/expansion_utils_d.c		\
		parsing/expansion/pre_expand_utils.c		\
		parsing/expansion/expansion_utils_c.c		\
		parsing/special_split.c						\
		parsing/syntax_handle.c						\
		execution/builtin/built_in.c				\
		execution/builtin/cd.c						\
		execution/builtin/unset.c					\
		execution/builtin/echo.c					\
		execution/builtin/exit.c					\
		execution/builtin/export.c					\
		execution/builtin/export_utils.c			\
		execution/execution.c						\
		execution/fork.c							\
		execution/get_next_line.c					\
		execution/redirections.c					\
		execution/utils_std.c						\
		execution/get_path.c						\
		execution/heredoc.c							\
		execution/error.c							\
		execution/signals.c							\
		execution/environment.c						\
		execution/environment_utils.c				\
		execution/list_utils.c						\
		execution/leaks_mem.c						\
		execution/leaks_fd.c						\
		execution/exit_status.c						\

HDR =	minishell.h									\
		libft/libft.h								\

OBJ = $(SRC:.c=.o)

BLUE = \033[34m
RED = \033[31m
RESET = \033[0m
GREEN = \033[32m

all: libft $(NAME)

libft:
	@$(MAKE) -C ./libft

$(NAME): $(OBJ) $(LIB)
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) $(LDFLAGS) -o $@ $(RFLG)
	@echo "$(GREEN)minishell	compiled successfully$(RESET)"

%.o: %.c $(HDR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C ./libft clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C ./libft fclean
	@echo "$(RED)minishell	cleanup$(RESET)"

re: fclean all

.PHONY: all libft clean fclean re
