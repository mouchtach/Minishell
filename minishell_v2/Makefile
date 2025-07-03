CC = cc
CFLAGS = -Wall -Wextra -Werror
RFLG = -lreadline -lncurses
NAME = minishell
READLINE_DIR = $(shell brew --prefix readline)
LIB = ./libft/libft.a

SRC = 	minishell.c									\
		./parsing/input/input.c						\
		./parsing/asm_cmd.c							\
		./parsing/tokens_core/list_tokens.c			\
		./parsing/tokens_core/refactor_tokens.c		\
		./parsing/tokens_core/unquotes.c			\
		./parsing/tokens_core/utils0_tokens.c		\
		./parsing/tokens_core/utils1_tokens.c		\
		./parsing/tokens_core/utils3_tokens.c		\
		./parsing/envp/env_expander.c				\
		./parsing/envp/env_list.c					\
		./parsing/envp/exp_special.c				\
		./parsing/envp/utils_env.c					\
		./parsing/envp/env_leaks.c					\
		./parsing/cmd/list_cmd.c					\
		./parsing/cmd/utils_cmd.c					\
		./parsing/cmd/nodes_cmd.c					\
		./parsing/cmd/content_cmd.c					\
		./parsing/syntax/scrap.c					\
		./parsing/syntax/utils_scrap.c				\
		./parsing/leaks/ffree.c						\
		./parsing/leaks/free_cmd_list.c				\
		./execution/builtin/built_in.c 				\
		./execution/builtin/cd.c 					\
		./execution/builtin/unset.c 				\
		./execution/builtin/echo.c 					\
		./execution/builtin/export.c				\
		./execution/execution.c 					\
		./execution/fork.c 							\
		./execution/get_next_line.c 				\
		./execution/redirections.c 					\
		./execution/utils_std.c 					\
		./execution/get_path.c						\
		./execution/heredoc.c						\
		./execution/clean.c							\
		./execution/error.c							\
		./execution/signals.c						\
		./execution/set_env.c						\

HDR = 		minishell.h 					\
		 	./parsing/include/token.h		\
		 	./parsing/include/syntax.h		\

OBJ = $(SRC:.c=.o)

SRC_LIB = 	./libft/ft_strjoin.c 	\
			./libft/ft_strdup.c 	\
			./libft/ft_strlen.c 	\
			./libft/ft_memcpy.c		\
			./libft/ft_substr.c		\
			./libft/ft_strncpy.c	\
			./libft/ft_isalpha.c	\
			./libft/ft_isdigit.c	\
			./libft/ft_isalnum.c	\
			./libft/ft_strcmp.c		\
			./libft/ft_strchr.c		\
			./libft/ft_split.c		\
			./libft/ft_putstr_fd.c  \
			./libft/ft_putchar_fd.c \
			./libft/ft_atoi.c       \

OBJ_LIB = $(SRC:.c=.o)

HDR_LIB = ./libft/libft.h

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) -I$(READLINE_DIR)/include -L$(READLINE_DIR)/lib -o $@ $(RFLG)

%.o: %.c $(HDR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIB): $(SRC_LIB) $(HDR_LIB)
	@$(MAKE) -C ./libft

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C ./libft clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C ./libft fclean

re: fclean all