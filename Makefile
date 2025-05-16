NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = srcs/main.c srcs/init.c srcs/map_parser.c srcs/map_checker.c \
	srcs/render.c srcs/player.c srcs/utils.c srcs/error.c srcs/map_utils.c \
	GNL/get_next_line.c GNL/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a
MLX42 = MLX42/bluid/libmlx42.a

DEPS = -lglfw -L "/opt/homebrew/Cellar/glfw/3.4/lib/" -framework Cocoa -framework OpenGL -framework IOKit

all: $(NAME)

$(NAME): $(LIBFT) $(MLX42) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(MLX42) $(DEPS) -I includes -I libft -I MLX42/includes

%srcs/.o: srcs/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ -I includes -I libft -I MLX42/includes

$(LIBFT):
	make -C libft

$(MLX42):
	cmake -B MLX42/bluid MLX42
	cmake --build MLX42/bluid -j4

clean:
	rm -rf $(OBJS)
	make -C libft clean
	rm -rf MLX42/bluid

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re