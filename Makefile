NAME = minishell
NAME_BONUS = $(NAME)_bonus

HEADER = $(NAME).h

SRC_PATH = srcs
PARS_PATH = $(SRC_PATH)/parsing
SRC = main.c utils.c path.c history.c gnl.c init.c
PARS_SRC = parsing.c parsing3.c utils.c tokens_utils.c check_syntax.c parsing2.c parsing4.c tokens_utils2.c utils2.c expand.c expand2.c env.c
BUILTINS_SRC = ft_cd.c ft_env.c ft_echo.c ft_exit.c ft_export.c ft_pwd.c ft_unset.c builtins_utils.c
EXEC_SRC = exec.c wait.c redirs.c redirs_utils.c path.c
SIGNALS_SRC = signals.c

SRC := $(addprefix $(SRC_PATH)/, $(SRC))
SRC += $(addprefix $(PARS_PATH)/, $(PARS_SRC))
SRC += $(addprefix $(SRC_PATH)/builtins/, $(BUILTINS_SRC))
SRC += $(addprefix $(SRC_PATH)/exec/, $(EXEC_SRC))
SRC += $(addprefix $(SRC_PATH)/signals/, $(SIGNALS_SRC))
OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 $(INCLUDES)

RM = rm -f

INCLUDES = -I $(LIBFT_PATH) -I.

LIBFT_PATH = includes/quoicoulibft
LIBFT = $(LIBFT_PATH)/libft.a

all : $(NAME)

$(LIBFT) :
	make --silent -C $(LIBFT_PATH)

$(NAME) : $(LIBFT) ${OBJ} $(HEADER) Makefile
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline

bonus: $(NAME)

clean :
	@ $(RM) $(NAME) $(OBJ)
	@make --silent clean -C $(LIBFT_PATH)

fclean :
	@ $(RM) $(NAME) $(NAME_BONUS)
	@ $(RM) $(NAME) $(OBJ)
	@make --silent fclean -C $(LIBFT_PATH)

re : fclean all

.PHONY : all clean fclean re
