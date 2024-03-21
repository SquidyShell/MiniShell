# PATH : /printfd
NAME		= ../objs/libftprintf.a

# COMPILATION
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

# FILES
SRCS		= ft_printfd.c ft_printf.c ft_putunsigned.c ft_putaddr.c ft_puthexa.c printfd.c printfd_utils.c
OBJS		= $(addprefix ../objs/, $(SRCS:.c=.o))

# TEXT
UP = \033[1A
ERASE = \033[0J

all: libft.a $(NAME) echo

$(NAME): $(OBJS)
	@ar rc $@ $^

../objs/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

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