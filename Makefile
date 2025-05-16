NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = srcs
OBJ_DIR = obj
INC_DIR = includes
LIBFT_DIR = libft
MLX42_DIR = MLX42
GNL_DIR = Get_Next_Line

SRC_FILES = main.c init.c map_parser.c map_checker.c render.c player.c utils.c error.c \
	map_utils.c \
	$(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c
	
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

LIBFT = $(LIBFT_DIR)/libft.a
MLX42 = $(MLX42_DIR)/bluid/libmlx42.a

DEPS = -lglfw -L "/opt/homebrew/Cellar/glfw/3.3.8/lib/" -framework Cocoa -framework OpenGL -framework IOKit

all: $(NAME)

$(NAME): $(LIBFT) $(MLX42) $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(MLX42) $(DEPS) -I $(INC_DIR) -I $(LIBFT_DIR) -I $(MLX42_DIR)/includes

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR) -I $(LIBFT_DIR) -I $(MLX42_DIR)/includes

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX42):
	cmake -B $(MLX42_DIR)/bluid $(MLX42_DIR)
	cmake --build $(MLX42_DIR)/bluid -j4

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean
	rm -rf $(MLX42_DIR)/bluid

fclean:
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re