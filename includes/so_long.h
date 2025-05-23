/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 00:43:40 by juan-jof          #+#    #+#             */
/*   Updated: 2025/05/23 19:50:12 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../Libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "../GNL/get_next_line.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

# define EMPTY '0'
# define WALL '1'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define PLAYER 'P'

# define TILE_SIZE 64

# define ERR_ARGS "Error: Incorrect number of arguments\n"
# define ERR_FILE "Error :Unable to open map file\n"
# define ERR_EXTENSION "Error: The map must have a .ber extension\n"
# define ERR_MAP_INVALID "Error: Invalid map\n"
# define ERR_MAP_NOT_RECTANGULAR "Error: The map must be rectangular\n"
# define ERR_MAP_NOT_SURROUNDED "Error: The map must be surrounded by walls\n"
# define ERR_MAP_CHARS "Error: Invalid characters on the map\n"
# define ERR_MAP_PLAYER "Error: There must be exactly one player (P)\n"
# define ERR_MAP_EXIT "Error: There must be at least one output (E)\n"
# define ERR_MAP_COLLECTIBLE \
	"Error: There must be at least one collectible (C)\n"
# define ERR_PATH "Error: There is no valid way to complete the game\n"
# define ERR_MEMORY "Error: Memory allocation failure\n"
# define ERR_MLX "Error: Failure to initialize MLX42º\n"
# define ERR_TEXTURE "Error: Could not load a texture\n"

typedef struct s_position
{
	int	x;
	int	y;
}	t_position;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	int			collectibles;
	int			exits;
	int			players;
	t_position	player_pos;	
}	t_map;

typedef struct s_textures
{
	mlx_texture_t	*wall;
	mlx_texture_t	*empty;
	mlx_texture_t	*collectible;
	mlx_texture_t	*exit;
	mlx_texture_t	*player;
}	t_textures;

typedef struct s_images
{
	mlx_image_t	*wall;
	mlx_image_t	*empty;
	mlx_image_t	*collectible;
	mlx_image_t	*exit;
	mlx_image_t	*player;
}	t_images;

typedef struct s_game
{
	mlx_t		*mlx;
	t_map		map;
	t_textures	textures;
	t_images	images;
	int			moves;
	int			collected;
	int			game_over;	
}	t_game;

// Initialization functions
t_game	*init_game(void);
int		init_window(t_game *game);
int		load_textures(t_game *game);
int		create_images(t_game *game);

// Map parsing functions
int		parse_map(t_game *game, char *file_path);
int		read_map_file(t_game *game, char *file_path);
int		check_map_dimensions(t_game *game);
int		validate_map_element(t_game *game);
int		add_line_to_grid(t_game *game, char *line);
void	remove_newline_if_exists(char *line);
void	count_elements(t_game *game, int x, int y, char c);
int		read_lines(t_game *game, int fd);
char	*get_next_line(int fd);

// Map validation functions
int		check_map_validity(t_game *game);
int		is_surrounded_by_walls(t_game *game);
char	**duplicate_map(t_map *map);
int		flood_fill(char **temp_map, int x, int y, t_map *map);
int		has_valid_path(t_game *game);

// Rendering functions
void	render_map(t_game *game);
void	render_tile(t_game *game, int x, int y);
void	update_player_position(t_game *game, int new_x, int new_y);
void	update_moves_counter(t_game *game);

// Player movement functions
void	hook_keys(mlx_key_data_t keydata, void *param);
int		move_player(t_game *game, int dx, int dy);
int		check_collision(t_game *game, int x, int y);
void	collect_item(t_game *game, int x, int y);
int		check_exit(t_game *game);

// utility functions
int		is_valid_map_char(char c);
int		check_file_extension(char *file_path, char *extension);
void	count_map_elements(t_game *game);
int		check_element_counts(t_game *game);

// Cleanup and error functions
void	free_map(t_map *map);
void	free_textures(t_textures *textures);
void	free_images(t_game *game);
void	free_game(t_game *game);
void	clean_exit(t_game *game);
void	print_error(char *error_message);
void	handle_close(void *param);

#endif