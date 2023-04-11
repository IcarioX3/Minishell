# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbled <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/22 01:30:53 by nbled             #+#    #+#              #
#    Updated: 2023/02/22 01:31:50 by nbled            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS =	list/ft_lstnew.c \
		list/ft_lstsize.c \
		list/ft_lstlast.c \
		list/ft_lstclear.c \
		list/ft_lstadd_back.c \
		split/ft_split.c \
		split/ft_isasep.c \
		split/ft_str_len.c \
		split/ft_count_words.c \
		quote_check.c \
		test.c 

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror


all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME} -lreadline

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
