# Path: /minmax

NAME = minmax.a

SRC = ft_min_max.c
OBJ = $(SRC:.c=.o)

CC = cc 
FLAGS = -Wall -Wextra -Werror

UP = \033[1A
ERASE = \033[0J

all: ccc $(NAME) echo

$(NAME): $(OBJ)
	@ar rc $@ $^

ccc:
	@$(CC) $(FLAGS) -c $(SRC)

echo:
	@echo "$(UP)$(ERASE)         \033[32mGreenlight minmax!\033[0m"

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re
