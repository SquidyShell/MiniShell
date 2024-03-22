# PATH : /
NAME = libft.a

# FILES
GD = gnl
PD = printfd
MD = minmax
LD = libft
G = $(GD).a
P = libftprintf.a
M = $(MD).a
L = $(LD).a
H = ./libft.h

# COMMANDS
MS = make --silent
MFCLEAN = make --silent fclean -C

# TEXT
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
MAGENTA = \033[1;35m
CYAN = \033[1;36m
WHITE = \033[1;37m
PURPLE = \033[38;5;105m
PINK = \033[38;5;206m
BOLD = \033[1m
UNDERLINE = \033[4m
RESET = \033[0m
UP = \033[1A
ERASE = \033[0J

OBJS_FILES = ft_atoi.o ft_isascii.o ft_lstadd_front_bonus.o ft_lstmap_bonus.o ft_memcpy.o ft_printfd.o \
		ft_putnbr_fd.o ft_split_charset_utils.o ft_strjoin.o ft_strncmp.o ft_tolower.o libftprintf.a \
			 ft_bzero.o ft_isdigit.o ft_lstclear_bonus.o ft_lstnew_bonus.o ft_memmove.o ft_putaddr.o \
			 ft_putstr_fd.o ft_split_utils.o ft_strlcat.o ft_strnstr.o ft_toupper.o minmax.a ft_calloc.o \
			 ft_isprint.o ft_lstdelone_bonus.o ft_lstsize_bonus.o ft_memset.o ft_putchar_fd.o \
			 ft_putunsigned.o ft_strchr.o ft_strdup.o ft_strlen.o ft_strrchr.o get_next_line.o printfd.o \
			 ft_isalnum.o ft_itoa.o ft_lstiter_bonus.o ft_memchr.o ft_min_max.o ft_putendl_fd.o ft_split.o \
			 ft_striteri.o ft_strlcpy.o ft_strtrim.o gnl.a printfd_utils.o ft_isalpha.o ft_lstadd_back_bonus.o \
			 ft_lstlast_bonus.o ft_memcmp.o ft_printf.o ft_puthexa.o ft_split_charset.o ft_strmapi.o ft_substr.o libft.a
OBJS = $(addprefix objs/, $(OBJS_FILES))

all: check_libft

check_libft:
		$(MS) making; \
		$(MS) $(NAME); \
		$(MS) echo; \


$(NAME):
	@$(MS) -C $(PD)
	@$(MS) -C $(GD)
	@$(MS) -C $(MD)
	@ar rc $(NAME) $(OBJS)


echo:
	@echo "$(UP)$(UP)$(ERASE)$(GREEN)  ● Made QuoicouLibft$(RESET)"

making:
	@echo "$(GREEN)🦑🦑🦑 Making QuoicouLibft... 🦑🦑🦑$(RESET)"

oclean:
	@$(MFCLEAN) $(LD)
	@$(MFCLEAN) $(GD)
	@$(MFCLEAN) $(PD)
	@$(MFCLEAN) $(MD)

clean: clean_o clean_a 
	@echo "$(BOLD)$(PINK)🦑🦑🦑 Crampting QuoicouLibft... 🦑🦑🦑$(RESET)"
	@$(MFCLEAN) $(LD)
	@echo "$(PINK)         Redlight FIRST LIBFT!$(RESET)"
	@$(MFCLEAN) $(GD)
	@echo "$(UP)$(ERASE)$(PINK)              Redlight GNL!$(RESET)"
	@$(MFCLEAN) $(PD)
	@echo "$(UP)$(ERASE)$(PINK)            Redlight PRINTFs!$(RESET)"
	@$(MFCLEAN) $(MD)
	@echo "$(UP)$(ERASE)$(PINK)            Redlight MINMAX!$(RESET)"

fclean:
	@if [ -f $(NAME) ]; then \
			$(MS) fclean_no_check; \
	fi

fclean_no_check: clean
	@rm -f $(NAME) 
	@echo "$(UP)$(UP)$(ERASE)$(BOLD)$(PINK)● QuoicouLibft Crampted$(RESET)"

re: fclean all

clean_o:
	@rm -f $(OBJS)

clean_a:
	@rm -f $(G) $(P) $(M)