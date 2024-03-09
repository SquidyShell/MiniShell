NAME = minishell
NAME_BONUS = $(NAME)_bonus

HEADER = $(NAME).h

SRC_PATH = srcs
PARS_PATH = $(SRC_PATH)/parsing
SRC = main.c
PARS_SRC = parsing.c utils.c tokens_utils.c

SRC := $(addprefix $(SRC_PATH)/, $(SRC))
SRC += $(addprefix $(PARS_PATH)/, $(PARS_SRC))
OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 $(INCLUDES)

RM = rm -f

INCLUDES = -I $(LIBFT_PATH) -I.

LIBFT_PATH = includes/quoicoulibft
LIBFT = $(LIBFT_PATH)/libft.a

all : $(NAME)

$(LIBFT) :
	make -C $(LIBFT_PATH)

$(NAME) : $(LIBFT) ${OBJ} $(HEADER) Makefile
	$(CC) $(CFLAGS) -o $(NAME) -lreadline $(OBJ) $(LIBFT)

bonus: $(NAME)

clean :
	@ $(RM) $(NAME) $(OBJ)
	@make clean -C $(LIBFT_PATH)

fclean :
	@ $(RM) $(NAME) $(NAME_BONUS)
	@ $(RM) $(NAME) $(OBJ)
	@make fclean -C $(LIBFT_PATH)

re : fclean all

.PHONY : all clean fclean re
