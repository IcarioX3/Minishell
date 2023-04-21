##### Colors ####
GREEN 	= \033[0;32m
RED 	= \033[0;31m
BLUE 	= \033[0;34m
END		= \033[0m

##### Names #####
NAME	= minishell
LIBNAME	= libft.a
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -lreadline

SRCDIR	= src
OBJDIR	= obj
INCDIR	= inc
LIBDIR	= libft

PARSING_DIR = parsing
DEBUG_DIR	= debug
UTILS_DIR	= utils
ERROR_DIR	= error
BUILTIN_DIR	= builtin

PARSING 	= lexer.c \
			parser.c \
			s_quote_parser.c \
			d_quote_parser.c \
			env_var_parser.c

LST			= lst_token.c

DEBUG		= print_tokens.c

UTILS		= parsing_utils.c \
			lst_token_utils.c

ERROR		= error.c

BUILTIN		= builtin.c

SRC_PARSING = $(addprefix $(PARSING_DIR)/, $(PARSING))
SRC_DEBUG	= $(addprefix $(DEBUG_DIR)/, $(DEBUG))
SRC_UTILS	= $(addprefix $(UTILS_DIR)/, $(UTILS))
SRC_ERROR	= $(addprefix $(ERROR_DIR)/, $(ERROR))
SRC_BUILTIN	= $(addprefix $(BUILTIN_DIR)/, $(BUILTIN))

_SRC		= main.c \
			signal.c \
			$(SRC_PARSING) \
			$(SRC_DEBUG) \
			$(SRC_UTILS) \
			$(SRC_ERROR) \
			$(SRC_BUILTIN)
		
SRC			= $(addprefix $(SRCDIR)/, $(_SRC))
OBJ			= $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)
HEADER 		= $(addprefix $(INCDIR)/, $(NAME).h)

##### Makefile work ####
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER)
	@mkdir -p $(@D)
	@$(CC) -c $(CFLAGS) -I$(LIBDIR) -I$(INCDIR) $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@echo "Baking $(LIBDIR)..."
	@make -s -C $(LIBDIR)
	@echo "$(GREEN)OK!$(END)"
	@echo "Baking $(NAME)..."
	@$(CC) -I$(INCDIR) -I$(LIBDIR) -o $@ $^ $(LIBDIR)/$(LIBNAME) $(CFLAGS) 
	@echo "$(GREEN)OK!$(END)"
	@echo "$(BLUE)$(NAME) READY !$(END)"

clean:
	@echo "Removing objects..."
	@make clean -s -C $(LIBDIR)
	@rm -rf $(OBJDIR)
	@echo "$(GREEN)Done!$(END)"

fclean: clean
	@echo "Cleaning everything..."
	@make fclean -s -C $(LIBDIR)
	@rm -f $(NAME)
	@echo "$(GREEN)Done!$(END)"
	@echo "$(BLUE)Everything is clean!$(END)"

re: fclean all

.PHONY: all clean fclean re