
SRC = libft.c main.c set_struct.c set_env.c set_path.c
OBJ = $(SRC:.c=.o)

CC = gcc
# CFLAGS = -Wall -Wextra -Werror 

all : $(OBJ)
	@echo "Compiling..."
	@$(CC) $(CFLAGS) $(OBJ)
	@echo "Done."

clean :
	@echo "Cleaning up..."
	@rm -f $(OBJ)
	@echo "Done."

fclean : clean
	@rm -f $(OBJ)
	@rm -f a.out