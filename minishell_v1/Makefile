NAME = minishell
HEADER = minishell.h
CC = cc
LDLIBS = -lreadline
CFLAGS = -Wall -Wextra -Werror
LIBFT = ./libft/libft.a
SRC =	minishell.c \
		./parssing/parse_redir.c \
		./parssing/redirection.c \
		./parssing/syntax_handle.c \
		./parssing/utils_a.c \
		./parssing/utils_b.c \
		./builtin/built_in.c \
		./builtin/cd.c \
		./builtin/echo.c \
		./builtin/export.c \
		./execution/execution.c \
		./execution/fork.c \
		./execution/get_next_line.c \
		./execution/redirections.c \
		./execution/utils_std.c \
		./execution/get_path.c \
		./execution/heredoc.c \
		./execution/clean.c \
		./execution/set_env.c \

OBJS = $(SRC:.c=.o)

########### colors
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[1;92m
YELLOW = \033[1;93m
BLUE = \033[1;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m



all : $(NAME)

$(NAME): $(LIBFT) $(OBJS) 
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDLIBS)
	@echo "$(GREEN)$(NAME) compiled successfully!$(DEF_COLOR)"

%.o: %.c $(HEADER)
	@echo "$(GREEN)C o m p i l i n g $< ...$(DEF_COLOR)"
	@${CC} ${CFLAGS} -c $< -o $@

$(LIBFT):
	@echo "$(BLUE)Compiling the Library LIBFT ...$(DEF_COLOR)"
	@make -C ./libft

clean:
	@echo "$(YELLOW)Cleaning object files...$(DEF_COLOR)"
	@rm -f $(OBJS)
	@make clean -C ./libft

fclean: clean
	@echo "$(RED)Cleaning all files...$(DEF_COLOR)"
	@rm -f $(NAME)
	@make fclean -C ./libft

re: fclean all