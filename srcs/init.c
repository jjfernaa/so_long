/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 00:35:29 by juan-jof          #+#    #+#             */
/*   Updated: 2025/05/12 22:08:16 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

t_game	*init_game(void)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	ft_memset(game, 0, sizeof(t_game));
	game->moves = 0;
	game->collected = 0;
	game->game_over = 0;
	return (game);
}

int	init_window(t_game *game)
{
	int	window_width;
	int	window_height;

	window_width = game->map.width * TILE_SIZE;
	window_height = game->map.height * TILE_SIZE;
	if (window_width > 1920 || window_height > 1080)
	{
		ft_putstr_fd("Erorr: Error the map is too big\n", 2);
		return (0);
	}
	game->mlx = mlx_init(window_width, window_height, "so_long", false);
	if (!game->mlx)
	{
		ft_putstr_fd(ERR_MLX, 2);
		return (0);
	}
	return (1);
}

int	load_textures(t_game *game)
{
	game->textures.wall = mlx_load_png("textures/wall.png");
	game->textures.empty = mlx_load_png("textures/floor.png");
	game->textures.collectible = mlx_load_png("textures/collectible.png");
	game->textures.exit = mlx_load_png("textures/exit.png");
	game->textures.player = mlx_load_png("textures/player.png");
	if (!game->textures.wall || !game->textures.empty
		|| !game->textures.collectible || !game->textures.exit
		|| !game->textures.player)
	{
		ft_putstr_fd(ERR_TEXTURE, 2);
		free_textures(&game->textures);
		return (0);
	}
	return (1);
}

int	create_images(t_game *game)
{
	game->images.wall = mlx_texture_to_image(game->mlx, game->textures.wall);
	game->images.empty = mlx_texture_to_image(game->mlx, game->textures.empty);
	game->images.collectible = \
		mlx_texture_to_image(game->mlx, game->textures.collectible);
	game->images.exit = mlx_texture_to_image(game->mlx, game->textures.exit);
	game->images.player = \
		mlx_texture_to_image(game->mlx, game->textures.player);
	if (!game->images.wall || !game->images.empty
		|| !game->images.collectible || !game->images.exit
		|| !game->images.player)
	{
		ft_putstr_fd("Error: Unable to create images\n", 2);
		return (0);
	}
	return (1);
}
