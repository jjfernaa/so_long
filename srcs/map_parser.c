/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 00:35:36 by juan-jof          #+#    #+#             */
/*   Updated: 2025/05/22 22:02:38 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	parse_map(t_game *game, char *file_path)
{
	if (!read_map_file(game, file_path))
		return (0);
	if (!check_map_dimensions(game))
	{
		ft_putstr_fd(ERR_MAP_NOT_RECTANGULAR, 2);
		return (0);
	}
	if (!validate_map_element(game))
		return (0);
	return (1);
}

int	read_map_file(t_game *game, char *file_path)
{
	int		fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd(ERR_FILE, 2);
		return (0);
	}
	game->map.height = 0;
	game->map.grid = NULL;
	if (!read_lines(game, fd))
	{
		free_map(&game->map);
		close(fd);
		return (0);
	}
	close (fd);
	if (game->map.height == 0)
	{
		ft_putstr_fd(ERR_MAP_INVALID, 2);
		return (0);
	}
	game->map.width = ft_strlen(game->map.grid[0]);
	return (1);
}

int	check_map_dimensions(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.height)
	{
		if (ft_strlen(game->map.grid[i]) != (size_t)game->map.width)
			return (0);
		i++;
	}
	return (1);
}

int	validate_map_element(t_game *game)
{
	int		x;
	int		y;
	char	c;

	game->map.players = 0;
	game->map.exits = 0;
	game->map.collectibles = 0;
	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < game->map.width)
		{
			c = game->map.grid[y][x];
			if (!is_valid_map_char(c))
			{
				ft_putstr_fd(ERR_MAP_CHARS, 2);
				return (0);
			}
			count_elements(game, x, y, c);
		}
	}
	if (!check_element_counts(game))
		return (0);
	return (1);
}
