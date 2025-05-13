CC = cc
# CFLAGS = -Wall -Wextra -Werror
SRC = main.c set_struct.c set_env.c set_path.c get_next_line.c redirections.c
OBJ = $(SRC:.c=.o)

NAME = minishell

LIBFT_DIR = Lib_ft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "$(NAME) compiled successfully!"

%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@echo "Compiling libft..."
	@make -C $(LIBFT_DIR)
	@echo "libft compiled!"

clean:
	@echo "Cleaning object files..."
	@rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean
	@echo "Clean complete!"

fclean: clean
	@echo "Full clean..."
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "Full clean complete!"

re: fclean all