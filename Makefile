# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/31 15:53:05 by icario            #+#    #+#              #
#    Updated: 2023/04/06 16:04:16 by ablevin          ###   ########.fr        #
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
CFLAGS	= -Wall -Werror -Wextra -lreadline

SRCDIR	= src
OBJDIR	= obj
INCDIR	= inc
LIBDIR	= libft

PARSING 	= parsing.c \
			prompt.c \

PARSING_DIR = parsing

SRC_PARSING = $(addprefix $(PARSING_DIR)/, $(PARSING))

_SRC		= main.c \
			$(SRC_PARSING)
		
SRC			= $(addprefix $(SRCDIR)/, $(_SRC))
OBJ			= $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)
HEADER 		= $(addprefix $(INCDIR)/, $(NAME).h)

##### Makefile work ####
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER)
	@mkdir -p $(@D)
	@mkdir -p $(OBJDIR)/$(PARSING_DIR)
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