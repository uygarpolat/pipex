# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 20:23:28 by upolat            #+#    #+#              #
#    Updated: 2024/06/08 13:01:34 by upolat           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC_DIR = src/mandatory
SRC_BONUS_DIR = src/bonus

SOURCES = 		$(SRC_DIR)/pipex.c \
                $(SRC_DIR)/handle_memory.c \
                $(SRC_DIR)/run_command.c \
                $(SRC_DIR)/handle_error.c $(SRC_DIR)/open_files_and_pipes.c \
                $(SRC_DIR)/handle_fork.c
SOURCES_BONUS = $(SRC_BONUS_DIR)/pipex_bonus.c $(SRC_BONUS_DIR)/here_doc_bonus.c \
                $(SRC_BONUS_DIR)/handle_memory_bonus.c \
                $(SRC_BONUS_DIR)/run_command_bonus.c \
                $(SRC_BONUS_DIR)/handle_error_bonus.c $(SRC_BONUS_DIR)/open_files_and_pipes_bonus.c \
                $(SRC_BONUS_DIR)/handle_fork_bonus.c

OBJECTS = $(SOURCES:.c=.o)
OBJECTS_BONUS = $(SOURCES_BONUS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

libft_dir := library/libft
libft := $(libft_dir)/libft.a

INCLUDES = -I./include -I$(libft_dir)

all: $(NAME)

$(NAME): $(OBJECTS) $(libft)
	cc $(CFLAGS) $(INCLUDES) -L$(libft_dir) -lft $^ -o $@

$(libft):
	$(MAKE) -C $(libft_dir)

bonus: .bonus

.bonus: $(OBJECTS_BONUS) $(libft)
	cc $(CFLAGS) $(INCLUDES) -L$(libft_dir) -lft $(OBJECTS_BONUS) -o $(NAME)
	@touch .bonus

%.o: %.c
	cc $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(OBJECTS_BONUS) .here_doc $(NAME) .bonus
	make -C $(libft_dir) clean

fclean: clean
	rm -f $(NAME) .here_doc
	make -C $(libft_dir) fclean

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re bonus rebonus
