# Path: /minmax

NAME = ../objs/minmax.a

SRC = ft_min_max.c
OBJ = $(addprefix ../objs/, $(SRC:.c=.o))

CC = cc 
FLAGS = -Wall -Wextra -Werror

UP = \033[1A
ERASE = \033[0J

all: $(NAME) echo

$(NAME): $(OBJ)
	@ar rc $@ $^

../objs/%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

echo:
	@echo "$(UP)$(ERASE)         \033[32mGreenlight minmax!\033[0m"

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re