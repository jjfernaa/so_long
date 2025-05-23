NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRCS = srcs/main.c srcs/init.c srcs/map_parser.c srcs/map_checker.c \
	srcs/render.c srcs/player.c srcs/utils.c srcs/error.c srcs/map_utils.c \
	GNL/get_next_line.c GNL/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

LIBFT = Libft/libft.a
MLX42 = MLX42/build/libmlx42.a

DEPS = -lglfw -lGL

all: $(NAME)

$(NAME): $(LIBFT) $(MLX42) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(MLX42) $(DEPS)
# -I includes -I Libft -I MLX42/includes

%srcs/.o: srcs/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ -I includes -I Libft -I MLX42/includes

$(LIBFT):
	make -C Libft

$(MLX42):
	cmake -B MLX42/build MLX42
	cmake --build MLX42/build -j4

clean:
	rm -rf $(OBJS)
	make -C Libft clean
	rm -rf MLX42/build

fclean: clean
	rm -f $(NAME)
	make -C Libft fclean

re: fclean all

val:
	valgrind -s --leak-check=full --show-leak-kinds=all ./so_long maps/map_medium.ber


val-sup:
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=solong.supp ./so_long maps/map_big.ber

.PHONY: all clean fclean re