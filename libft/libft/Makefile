# PATH : /libft
NAME		= ../objs/libft.a

# COMPILATION
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3

# FILES
SRCS		=	ft_striteri.c ft_strmapi.c ft_putnbr_fd.c ft_putchar_fd.c \
				ft_putstr_fd.c ft_putendl_fd.c ft_itoa.c ft_split.c ft_strtrim.c \
				ft_strjoin.c ft_substr.c ft_calloc.c ft_strdup.c ft_atoi.c \
				ft_isalpha.c ft_isprint.c ft_memset.c ft_memchr.c ft_memcmp.c \
				ft_strlcpy.c ft_strnstr.c ft_toupper.c ft_bzero.c ft_isascii.c \
				ft_memcpy.c ft_strchr.c ft_strlen.c ft_strrchr.c ft_isalnum.c \
				ft_isdigit.c ft_memmove.c ft_strlcat.c ft_strncmp.c ft_tolower.c \
				ft_split_charset.c ft_split_charset_utils.c ft_split_utils.c
BONUS_SRCS	=	ft_lstmap_bonus.c ft_lstiter_bonus.c ft_lstclear_bonus.c \
				ft_lstdelone_bonus.c ft_lstadd_back_bonus.c ft_lstlast_bonus.c \
				ft_lstsize_bonus.c ft_lstadd_front_bonus.c ft_lstnew_bonus.c
OBJS		= $(addprefix ../objs/, $(SRCS:.c=.o))
BONUS_OBJS	= $(addprefix ../objs/, $(BONUS_SRCS:.c=.o))

all: ../objs $(NAME) bonus

../objs:
	mkdir -p ../objs

../objs/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@ar rc $@ $^

bonus: $(BONUS_OBJS)
	@ar rc $(NAME) $^

_bonus.o: _bonus.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all