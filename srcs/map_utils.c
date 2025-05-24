/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 01:34:48 by juan-jof          #+#    #+#             */
/*   Updated: 2025/05/24 03:51:00 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	add_line_to_grid(t_game *game, char *line)
{
	char	**temp;
	int		i;

	temp = malloc(sizeof(char *) * (game->map.height + 2));
	if (!temp)
		return (0);
	i = 0;
	while (i < game->map.height)
	{
		temp[i] = game->map.grid[i];
		i++;
	}
	temp[i] = line;
	temp[i + 1] = NULL;
	free(game->map.grid);
	game->map.grid = temp;
	game->map.height++;
	return (1);
}

void	remove_newline_if_exists(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

void	count_elements(t_game *game, int x, int y, char c)
{
	if (c == PLAYER)
	{
		game->map.players++;
		game->map.player_pos.x = x;
		game->map.player_pos.y = y;
	}
	else if (c == EXIT)
		game->map.exits++;
	else if (c == COLLECTIBLE)
		game->map.collectibles++;
}

int	read_lines(t_game *game, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (ft_strlen(line) <= 1 && line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		remove_newline_if_exists(line);
		if (!add_line_to_grid(game, line))
		{
			free(line);
			close(fd);
			return (0);
		}
		line = get_next_line(fd);
	}
	return (1);
}

int	check_element_counts(t_game *game)
{
	if (game->map.players != 1)
	{
		ft_putstr_fd(ERR_MAP_PLAYER, 2);
		return (0);
	}
	if (game->map.exits < 1 || game->map.exits > 1)
	{
		ft_putstr_fd(ERR_MAP_EXIT, 2);
		return (0);
	}
	if (game->map.collectibles < 1)
	{
		ft_putstr_fd(ERR_MAP_COLLECTIBLE, 2);
		return (0);
	}
	return (1);
}
