# PATH : /printfd
NAME		= libftprintf.a

# COMPILATION
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

# FILES
SRCS		= ft_printfd.c ft_printf.c ft_putunsigned.c ft_putaddr.c ft_puthexa.c printfd.c
OBJS		= $(SRCS:.c=.o)

# TEXT
UP = \033[1A
ERASE = \033[0J

all: libft.a $(NAME) echo clean

.o: .c ${INCLUDE}
	$(CC) $(CFLAGS) -o $(SRCS) $(OBJS)

$(NAME): $(OBJS)
	@cp ../libft/libft.a $@
	@ar rc $@ $^

libft.a:
	@make --silent -C ../libft

clean:
	@rm -f $(OBJS)
	@make --silent clean -C ../libft

echo: #echo "Made printf!" en vert
	@echo "$(UP)$(ERASE)\033[32m         Greenlight printfs!\033[0m"

fclean: clean
	@rm -f $(NAME)

re: fclean all