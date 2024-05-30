# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/23 16:24:12 by upolat            #+#    #+#              #
#    Updated: 2024/05/30 15:28:07 by upolat           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus

SOURCES = 		./pipex.c ./ft_split_3.c
SOURCES_BONUS = ./pipex_bonus.c ./here_doc_bonus.c \
				./close_and_free_bonus.c ./memory_handling_bonus.c \
				./run_command_bonus.c ./ft_split_3.c \
				./error_handler.c

OBJECTS = $(SOURCES:.c=.o)
OBJECTS_BONUS = $(SOURCES_BONUS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

libft_dir := ./libft
libft := $(libft_dir)/libft.a

INCLUDES = -I./pipex.h -I$(libft_dir)
INCLUDES_BONUS = -I./pipex_bonus.h -I$(libft_dir)

all: $(NAME)

$(libft):
	make -C $(libft_dir)

$(NAME): $(libft) $(OBJECTS)
	cc $(CFLAGS) $(INCLUDES) $^ -o $@

bonus: .bonus

.bonus: $(NAME) $(NAME_BONUS)
	@touch .bonus

$(NAME_BONUS): $(libft) $(OBJECTS_BONUS)
	cc $(CFLAGS) $(INCLUDES_BONUS) $^ -o $@

%.o : %.c
	cc $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(OBJECTS_BONUS)
	make -C $(libft_dir) clean

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	make -C $(libft_dir) fclean
	rm -f .bonus

re:	fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re bonus rebonus
