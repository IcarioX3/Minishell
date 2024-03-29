# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/20 13:04:56 by ablevin           #+#    #+#              #
#    Updated: 2023/05/20 13:12:15 by ablevin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##### Colors ####
GREEN 	= \033[0;32m
RED 	= \033[0;31m
BLUE 	= \033[0;34m
END		= \033[0m

##### Names #####
NAME	= minishell
LIBNAME	= libft.a
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -lreadline -g3

SRCDIR	= src
OBJDIR	= obj
INCDIR	= inc
LIBDIR	= libft

PARSING_DIR = parsing
BLOCKS_DIR	= blocks
DEBUG_DIR	= debug
UTILS_DIR	= utils
ERROR_DIR	= error
BUILTIN_DIR	= builtin
EXEC_DIR	= exec

PARSING 	= lexer.c \
			parser.c \
			s_quote_parser.c \
			d_quote_parser.c \
			env_var_parser.c \
			split_dollar.c \
			check_parse_error.c \
			redir_parser.c \

BLOCKS		= blocks.c \
			blocks_redir.c \

DEBUG		= print_tokens.c \
			print_blocks.c \

UTILS		= parsing_utils.c \
			lst_token_utils.c \
			lst_blocks_utils.c \
			get_env.c \
			clean.c \
			env_to_array.c \
			check_redir_exec.c \
			is_heredoc.c \

ERROR		= error.c

BUILTIN		= builtin.c \
			cd.c \
			echo.c \
			env.c \
			export.c \
			pwd.c \
			unset.c \
			utils_builtin.c \
			utils_builtin2.c \
			exit.c \
			cd2.c \
			clear_exit.c \
			export2.c \

EXEC	= heredoc.c \
		exec.c \
		init_exec.c \
		get_path.c \
		open_files.c \
		child.c \
		check_before_exec.c \


SRC_PARSING = $(addprefix $(PARSING_DIR)/, $(PARSING))
SRC_DEBUG	= $(addprefix $(DEBUG_DIR)/, $(DEBUG))
SRC_UTILS	= $(addprefix $(UTILS_DIR)/, $(UTILS))
SRC_ERROR	= $(addprefix $(ERROR_DIR)/, $(ERROR))
SRC_BLOCKS	= $(addprefix $(BLOCKS_DIR)/, $(BLOCKS))
SRC_BUILTIN	= $(addprefix $(BUILTIN_DIR)/, $(BUILTIN))
SRC_EXEC	= $(addprefix $(EXEC_DIR)/, $(EXEC))

_SRC		= main.c \
			signal.c \
			$(SRC_PARSING) \
			$(SRC_DEBUG) \
			$(SRC_UTILS) \
			$(SRC_ERROR) \
			$(SRC_BLOCKS) \
			$(SRC_BUILTIN) \
			$(SRC_EXEC) \
		
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