NAME = pipex

# Source directories
SRC_DIR = src/mandatory
SRC_BONUS_DIR = src/bonus

# Source files
SOURCES = 		$(SRC_DIR)/pipex.c $(SRC_DIR)/here_doc.c \
                $(SRC_DIR)/memory_handling.c $(SRC_DIR)/paths.c \
                $(SRC_DIR)/run_command.c $(SRC_DIR)/ft_split_3.c \
                $(SRC_DIR)/error_handler.c $(SRC_DIR)/open_files.c
SOURCES_BONUS = $(SRC_BONUS_DIR)/pipex_bonus.c $(SRC_BONUS_DIR)/here_doc_bonus.c \
                $(SRC_BONUS_DIR)/memory_handling_bonus.c $(SRC_BONUS_DIR)/paths_bonus.c \
                $(SRC_BONUS_DIR)/run_command_bonus.c $(SRC_BONUS_DIR)/ft_split_3.c \
                $(SRC_BONUS_DIR)/error_handler_bonus.c $(SRC_BONUS_DIR)/open_files_bonus.c \
                $(SRC_BONUS_DIR)/handle_fork_bonus.c


# Object files
OBJECTS = $(SOURCES:.c=.o)
OBJECTS_BONUS = $(SOURCES_BONUS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

# libft configuration
libft_dir := lib/libft
libft := $(libft_dir)/libft.a

# Include directories
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

# Pattern rule for object files
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

