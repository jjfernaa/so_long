/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 00:35:41 by juan-jof          #+#    #+#             */
/*   Updated: 2025/05/23 19:43:02 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			render_tile(game, x, y);
			x++;
		}
		y++;
	}
}

void	render_tile(t_game *game, int x, int y)
{
	int	pixel_x;
	int	pixel_y;

	pixel_x = x * TILE_SIZE;
	pixel_y = y * TILE_SIZE;
	mlx_image_to_window(game->mlx, game->images.empty, pixel_x, pixel_y);
	if (game->map.grid[y][x] == WALL)
		mlx_image_to_window(game->mlx, game->images.wall, pixel_x, pixel_y);
	else if (game->map.grid[y][x] == COLLECTIBLE)
		mlx_image_to_window(game->mlx, game->images.collectible,
			pixel_x, pixel_y);
	else if (game->map.grid[y][x] == EXIT)
		mlx_image_to_window(game->mlx, game->images.exit, pixel_x, pixel_y);
	else if (game->map.grid[y][x] == PLAYER)
		mlx_image_to_window(game->mlx, game->images.player, pixel_x, pixel_y);
}

void	update_player_position(t_game *game, int new_x, int new_y)
{
	mlx_image_to_window(game->mlx, game->images.empty,
		game->map.player_pos.x * TILE_SIZE,
		game->map.player_pos.y * TILE_SIZE);
	mlx_image_to_window(game->mlx, game->images.player, new_x * TILE_SIZE,
		new_y * TILE_SIZE);
	game->map.grid[game->map.player_pos.y][game->map.player_pos.x] = EMPTY;
	game->map.grid[new_y][new_x] = PLAYER;
	game->map.player_pos.x = new_x;
	game->map.player_pos.y = new_y;
	update_moves_counter(game);
}

void	update_moves_counter(t_game *game)
{
	char	*moves_str;
	char	*msg;

	game->moves++;
	moves_str = ft_itoa(game->moves);
	if (!moves_str)
		return ;
	msg = ft_strjoin("movements:", moves_str);
	if (!msg)
	{
		free (moves_str);
		return ;
	}
	ft_putchar_fd('\r', 1);
	ft_putstr_fd(msg, 1);
	free(moves_str);
	free(msg);
}
