/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 00:35:38 by juan-jof          #+#    #+#             */
/*   Updated: 2025/05/22 20:39:09 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	hook_keys(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (game->game_over)
	{
		if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
			mlx_close_window(game->mlx);
		return ;
	}
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_W)
			move_player(game, 0, -1);
		else if (keydata.key == MLX_KEY_A)
			move_player(game, -1, 0);
		else if (keydata.key == MLX_KEY_S)
			move_player(game, 0, 1);
		else if (keydata.key == MLX_KEY_D)
			move_player(game, 1, 0);
		else if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
	}
}

int	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->map.player_pos.x + dx;
	new_y = game->map.player_pos.y + dy;
	if (check_collision(game, new_x, new_y))
		return (0);
	if (game->map.grid[new_y][new_x] == COLLECTIBLE)
		collect_item(game, new_x, new_y);
	if (game->map.grid[new_y][new_x] == EXIT)
	{
		if (check_exit(game))
		{
			game->game_over = 1;
			ft_putstr_fd("\nCongrats! You have completed the game\n", 1);
			mlx_close_window(game->mlx);
			return (1);
		}
		return (0);
	}
	update_player_position(game, new_x, new_y);
	return (1);
}

int	check_collision(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map.width || y >= game->map.height)
		return (1);
	if (game->map.grid[y][x] == WALL)
		return (1);
	return (0);
}

void	collect_item(t_game *game, int x, int y)
{
	game->collected++;
	game->map.grid[y][x] = EMPTY;
	ft_putstr_fd("\nCollectible collected\n", 1);
	ft_putnbr_fd(game->collected, 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(game->map.collectibles, 1);
	ft_putchar_fd('\n', 1);
}

int	check_exit(t_game *game)
{
	return (game->collected == game->map.collectibles);
}
