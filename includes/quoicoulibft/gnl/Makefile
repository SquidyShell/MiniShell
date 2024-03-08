# PATH : /libft
NAME = gnl.a

# COMPILATION
CC = cc 
FLAGS = -Wall -Wextra -Werror

# FILES
SRC = get_next_line.c \
		get_next_line_utils.c
OBJ = $(SRC:.c=.o)

# TEXT
UP = \033[1A
ERASE = \033[0J

all: libft.a ccc $(NAME) echo 

$(NAME): $(OBJ)
	@ar rc $@ $^

libft.a:
	@make --silent -C ../libft
	@echo "       \033[32mGreenlight first libft!\033[0m"
	@cp ../libft/libft.a $(NAME)

ccc:
	@cc -Wall -Wextra -Werror -c get_next_line.c -I .

echo:
	@echo "$(UP)$(ERASE)         \033[32m Greenlight gnl!\033[0m"

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re