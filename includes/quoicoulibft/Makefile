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

all: check_libft

check_libft:
	@if [ ! -f $(NAME) ]; then \
			$(MS) making; \
			$(MS) $(NAME); \
			$(MS) echo; \
	fi

$(NAME):
	@$(MS) -C $(GD)
	@$(MS) -C $(PD)
	@$(MS) -C $(MD)
	@cp $(PD)/$(P) $(NAME)
	@cp $(GD)/$(G) .
	@cp $(MD)/$(M) .
	@ar x $(G)
	@ar x $(M)
	@ar rc $(NAME) *.o


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
	@rm -f *.o

clean_a:
	@rm -f $(G) $(P) $(M)