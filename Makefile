NAME = cub3D

CC = cc

CFLAGS = -Wall -fsanitize=address

SRCS = main.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
		parser/parsing.c parser/utils.c parser/read_file.c parser/check_file.c \
		parser/tokenize_data.c parser/extract_colors.c parser/extract_paths.c \
		parser/extract_map.c game.c

OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lmlx -lX11 -lXext -lm

$(LIBFT):
	make -C libft

clean:
	rm -f $(OBJS)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft
re: fclean all

.PHONY: all clean fclean re
