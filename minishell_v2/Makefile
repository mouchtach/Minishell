# Colors
BOLD	= \033[1m
GREEN	= \033[32;1m
BLUE	= \033[34;1m
YELLOW	= \033[33;1m
RED		= \033[31;1m
CYAN	= \033[36;1m
RESET	= \033[0m

# Compiler and flags
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RFLG	= -lreadline -lncurses
NAME	= minishell
READLINE_DIR = $(shell brew --prefix readline)
LIB		= ./libft/libft.a

# Source files
SRC =	minishell.c									\
		./parsing/history/history.c					\
		./parsing/signal/signal.c					\
		./parsing/asm_cmd.c							\
		./parsing/tokens_core/list_tokens.c			\
		./parsing/tokens_core/refactor_tokens.c		\
		./parsing/tokens_core/unquotes.c			\
		./parsing/tokens_core/utils0_tokens.c		\
		./parsing/tokens_core/utils1_tokens.c		\
		./parsing/tokens_core/utils3_tokens.c		\
		./parsing/envp/env_expander.c				\
		./parsing/envp/env_list.c					\
		./parsing/envp/env_split.c					\
		./parsing/envp/exp_special.c				\
		./parsing/envp/env_heredoc.c				\
		./parsing/envp/utils_env.c					\
		./parsing/envp/utils1_env.c					\
		./parsing/envp/env_leaks.c					\
		./parsing/cmd/list_cmd.c					\
		./parsing/cmd/utils_cmd.c					\
		./parsing/cmd/nodes_cmd.c					\
		./parsing/cmd/content_cmd.c					\
		./parsing/syntax/scrap.c					\
		./parsing/syntax/utils_scrap.c				\
		./parsing/leaks/ffree.c						\
		./parsing/leaks/free_cmd_list.c				\
		./execution/builtin/built_in.c				\
		./execution/builtin/cd.c					\
		./execution/builtin/unset.c					\
		./execution/builtin/echo.c					\
		./execution/builtin/exit.c					\
		./execution/builtin/export.c				\
		./execution/builtin/export_utils.c			\
		./execution/execution.c						\
		./execution/fork.c							\
		./execution/get_next_line.c					\
		./execution/redirections.c					\
		./execution/utils_std.c						\
		./execution/get_path.c						\
		./execution/heredoc.c						\
		./execution/error.c							\
		./execution/signals.c						\
		./execution/environment.c					\
		./execution/environment_utils.c				\
		./execution/list_utils.c					\
		./execution/leaks_mem.c						\
		./execution/leaks_fd.c						\
		./execution/exit_status.c					\

HDR =	minishell.h					\
		./parsing/include/syntax.h	\

OBJ = $(SRC:.c=.o)

all: libft $(NAME)

libft:
	@echo "$(CYAN)$(BOLD)📚 COMPILING LIBFT...$(RESET)"
	@$(MAKE) -C ./libft
	@echo "$(GREEN)$(BOLD)✅ LIBFT COMPILED!$(RESET)\n"

$(NAME): $(OBJ) $(LIB)
	@echo "$(CYAN)$(BOLD)🔗 LINKING $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) -I$(READLINE_DIR)/include -L$(READLINE_DIR)/lib -o $@ $(RFLG)
	@echo "$(GREEN)$(BOLD)🎉 SUCCESS: $(NAME) READY!$(RESET)\n"

%.o: %.c $(HDR)
	@case "$<" in \
		*parsing*) \
			echo "$(YELLOW)🧩 [Parsing] Compiling:\t$<$(RESET)";; \
		*execution*) \
			echo "$(BLUE)⚡ [Execution] Compiling:\t$<$(RESET)";; \
	esac
	@$(CC) $(CFLAGS) -I$(READLINE_DIR)/include -c $< -o $@

clean:
	@echo "$(RED)$(BOLD)🧹 CLEANING OBJECT FILES...$(RESET)"
	@rm -f $(OBJ)
	@$(MAKE) -C ./libft clean
	@echo "$(GREEN)$(BOLD)✅ OBJECTS CLEANED!$(RESET)\n"

fclean: clean
	@echo "$(RED)$(BOLD)🧹 REMOVING $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C ./libft fclean
	@echo "$(GREEN)$(BOLD)✅ FULL CLEAN COMPLETE!$(RESET)\n"

re: fclean all

.PHONY: all libft clean fclean re
