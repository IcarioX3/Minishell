# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: icario <icario@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/31 15:53:05 by icario            #+#    #+#              #
#    Updated: 2023/03/31 15:55:10 by icario           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##### Colors ####
GREEN 	= \033[0;32m
RED 	= \033[0;31m
BLUE 	= \033[0;34m
END	= \033[0m

##### Names #####
NAME	= minishell
CC	= gcc
CFLAGS	= -Wall -Werror -Wextra -g3 

SRCDIR	= src
OBJDIR	= obj
INCDIR	= inc

_SRC	= main.c
		
SRC	= $(addprefix $(SRCDIR)/, $(_SRC))
OBJ	= $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)
HEADER = $(addprefix $(INCDIR)/, $(NAME).h)

##### Makefile work ####
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER)
	@mkdir -p $(@D)
	@$(CC) -c $(CFLAGS) -I$(INCDIR) $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@echo "Baking $(NAME)..."
	@$(CC) -I$(INCDIR) -o $@ $^ $(CFLAGS) 
	@echo "$(GREEN)OK!$(END)"
	@echo "$(BLUE)$(NAME) READY !$(END)"

clean:
	@echo "Removing objects..."
	@rm -rf $(OBJDIR)
	@echo "$(GREEN)Done!$(END)"

fclean: clean
	@echo "Cleaning everything..."
	@rm -f $(NAME)
	@echo "$(GREEN)Done!$(END)"
	@echo "$(BLUE)Everything is clean!$(END)"

re: fclean all

.PHONY: all clean fclean re