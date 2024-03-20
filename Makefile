NAME = minishell
NAME_BONUS = $(NAME)_bonus

HEADER = $(NAME).h

SRC_PATH = srcs
PARS_PATH = $(SRC_PATH)/parsing
OBJ_PATH = objs

SRC = main.c

PARS_SRC = parsing.c env.c check_syntax.c
PARS_UTILS_SRC = utils.c tokens_utils.c tokens_utils2.c utils2.c utils3.c
PARS_HEREDOC_SRC = heredoc.c heredoc_expand.c heredoc_utils.c
PARS_CASES_SRC = quotes_handling.c type_cases.c type_cases2.c
PARS_EXPANDS_SRC = expand.c expand2.c wildcard_expand.c expand_utils.c
BUILTINS_SRC = ft_cd.c ft_env.c ft_echo.c ft_exit.c ft_export.c ft_export2.c \
				ft_export_print.c ft_pwd.c ft_unset.c builtins_utils.c
EXEC_SRC = exec.c wait.c redirs.c redirs_utils.c exec_utils.c
RL_NAME_SRC = update_rl_name.c
SIGNALS_SRC = signals.c
PATH_SRC = path.c path_utils.c
GNL_SRC = gnl.c
HISTORY_SRC = history.c
INIT_SRC = init.c

SRC := $(addprefix $(SRC_PATH)/, $(SRC))
SRC += $(addprefix $(PARS_PATH)/, $(PARS_SRC))
SRC += $(addprefix $(PARS_PATH)/utils/, $(PARS_UTILS_SRC))
SRC += $(addprefix $(PARS_PATH)/heredoc/, $(PARS_HEREDOC_SRC))
SRC += $(addprefix $(PARS_PATH)/cases/, $(PARS_CASES_SRC))
SRC += $(addprefix $(PARS_PATH)/expands/, $(PARS_EXPANDS_SRC))
SRC += $(addprefix $(SRC_PATH)/builtins/, $(BUILTINS_SRC))
SRC += $(addprefix $(SRC_PATH)/exec/, $(EXEC_SRC))
SRC += $(addprefix $(SRC_PATH)/signals/, $(SIGNALS_SRC))
SRC += $(addprefix $(SRC_PATH)/path/, $(PATH_SRC))
SRC += $(addprefix $(SRC_PATH)/gnl/, $(GNL_SRC))
SRC += $(addprefix $(SRC_PATH)/history/, $(HISTORY_SRC))
SRC += $(addprefix $(SRC_PATH)/init/, $(INIT_SRC))
SRC += $(addprefix $(SRC_PATH)/rl_name/, $(RL_NAME_SRC))

OBJ = $(patsubst %.c,$(OBJ_PATH)/%.o,$(SRC))

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 $(INCLUDES)

RM = rm -f

INCLUDES = -I $(LIBFT_PATH) -I.

LIBFT_PATH = includes/quoicoulibft
LIBFT = $(LIBFT_PATH)/libft.a

all : $(NAME)

$(LIBFT) :
	make --silent -C $(LIBFT_PATH)

$(OBJ_PATH)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(LIBFT) ${OBJ} $(HEADER) Makefile
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline

bonus: $(NAME)

clean :
	@ $(RM) -r $(OBJ_PATH)
	@make --silent clean -C $(LIBFT_PATH)

fclean : clean
	@ $(RM) $(NAME) $(NAME_BONUS)
	@make --silent fclean -C $(LIBFT_PATH)

re : fclean all

.PHONY : all clean fclean re