# PATH : /gnl
NAME = ../objs/gnl.a

# COMPILATION
CC = cc 
FLAGS = -Wall -Wextra -Werror

# FILES
SRC = get_next_line.c
OBJ = $(addprefix ../objs/, $(SRC:.c=.o))

# TEXT
UP = \033[1A
ERASE = \033[0J

all: $(NAME) echo 

$(NAME): $(OBJ)
	@ar rc $@ $^

../objs/%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

echo:
	@echo "$(UP)$(ERASE)         \033[32m Greenlight gnl!\033[0m"

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re