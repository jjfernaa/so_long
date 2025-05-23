/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 00:35:43 by juan-jof          #+#    #+#             */
/*   Updated: 2025/05/23 19:43:31 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_map(t_map *map)
{
	int	i;

	if (!map || !map->grid)
		return ;
	i = 0;
	while (i < map->height)
	{
		if (map->grid[i])
			free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}

void	free_textures(t_textures *textures)
{
	if (!textures)
		return ;
	if (textures->wall)
		mlx_delete_texture(textures->wall);
	if (textures->empty)
		mlx_delete_texture(textures->empty);
	if (textures->collectible)
		mlx_delete_texture(textures->collectible);
	if (textures->exit)
		mlx_delete_texture(textures->exit);
	if (textures->player)
		mlx_delete_texture(textures->player);
}

int	is_valid_map_char(char c)
{
	return (c == EMPTY || c == WALL || c == COLLECTIBLE || c == EXIT
		|| c == PLAYER);
}

int	check_file_extension(char *file_path, char *extension)
{
	size_t	file_len;
	size_t	ext_len;
	int		match;

	if (!file_path || !extension)
		return (0);
	file_len = ft_strlen(file_path);
	ext_len = ft_strlen(extension);
	if (file_len <= ext_len)
		return (0);
	match = ft_strncmp(file_path + file_len - ext_len, extension, ext_len) == 0;
	return (match);
}

void	count_map_elements(t_game *game)
{
	int	x;
	int	y;

	game->map.players = 0;
	game->map.exits = 0;
	game->map.collectibles = 0;
	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < game->map.width)
		{
			if (game->map.grid[y][x] == PLAYER)
			{
				game->map.players++;
				game->map.player_pos.x = x;
				game->map.player_pos.y = y;
			}
			else if (game->map.grid[y][x] == EXIT)
				game->map.exits++;
			else if (game->map.grid[y][x] == COLLECTIBLE)
				game->map.collectibles++;
		}
	}
}
