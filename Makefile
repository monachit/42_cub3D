NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = main.c

OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) 

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