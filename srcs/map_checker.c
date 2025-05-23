/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 00:35:34 by juan-jof          #+#    #+#             */
/*   Updated: 2025/05/23 19:40:36 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_map_validity(t_game *game)
{
	if (!is_surrounded_by_walls(game))
	{
		ft_putstr_fd(ERR_MAP_NOT_SURROUNDED, 2);
		return (0);
	}
	if (!has_valid_path(game))
	{
		ft_putstr_fd(ERR_PATH, 2);
		return (0);
	}
	return (1);
}

int	is_surrounded_by_walls(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->map.width)
	{
		if (game->map.grid[0][x] != WALL
			|| game->map.grid[game->map.height -1][x] != WALL)
			return (0);
		x++;
	}
	y = 0;
	while (y < game->map.height)
	{
		if (game->map.grid[y][0] != WALL
			|| game->map.grid[y][game->map.width - 1] != WALL)
			return (0);
		y++;
	}
	return (1);
}

char	**duplicate_map(t_map *map)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (map->height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		copy[i] = ft_strdup(map->grid[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	flood_fill(char **temp_map, int x, int y, t_map *map)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (1);
	if (temp_map[y][x] == WALL || temp_map[y][x] == 'V')
		return (1);
	temp_map[y][x] = 'V';
	flood_fill(temp_map, x + 1, y, map);
	flood_fill(temp_map, x - 1, y, map);
	flood_fill(temp_map, x, y + 1, map);
	flood_fill(temp_map, x, y - 1, map);
	return (1);
}

int	has_valid_path(t_game *game)
{
	char	**t;
	int		x;
	int		y;
	int		v;

	t = duplicate_map(&game->map);
	if (!t)
		return (0);
	flood_fill(t, game->map.player_pos.x, game->map.player_pos.y, &game->map);
	v = 1;
	y = -1;
	while (++y < game->map.height && v)
	{
		x = -1;
		while (++x < game->map.width && v)
			if ((game->map.grid[y][x] == COLLECTIBLE
				|| game->map.grid[y][x] == EXIT) && t[y][x] != 'V')
				v = 0;
	}
	y = -1;
	while (++y < game->map.height)
		free(t[y]);
	free(t);
	return (v);
}
