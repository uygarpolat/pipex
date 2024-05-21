# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/12 01:50:15 by upolat            #+#    #+#              #
#    Updated: 2024/05/21 14:42:58 by upolat           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
BONUS_NAME = pipex_bonus
SRC = pipex.c
BONUS_SRC = pipex_bonus.c
LIBFTPRINTF = libftprintf.a

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFTPRINTF)

bonus: $(NAME) $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJ) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $(BONUS_OBJ) -o $(BONUS_NAME) $(LIBFTPRINTF)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all bonus clean fclean re
