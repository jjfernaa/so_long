/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 00:35:29 by juan-jof          #+#    #+#             */
/*   Updated: 2025/05/23 19:38:32 by juan-jof         ###   ########.fr       */
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
	if (!game->textures.wall)
		ft_putstr_fd("Error: failed to load wall.png\n", 2);
	game->textures.empty = mlx_load_png("textures/floor.png");
	if (!game->textures.empty)
		ft_putstr_fd("Error: failed to load floor.png\n", 2);
	game->textures.collectible = mlx_load_png("textures/collectible.png");
	if (!game->textures.collectible)
		ft_putstr_fd("Error: failed to load collectible.png\n", 2);
	game->textures.exit = mlx_load_png("textures/exit.png");
	if (!game->textures.exit)
		ft_putstr_fd("Error: failed to load exit.png\n", 2);
	game->textures.player = mlx_load_png("textures/player.png");
	if (!game->textures.player)
		ft_putstr_fd("Error: failed to load player.png\n", 2);
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
	if (!game->images.wall)
		ft_putstr_fd("Error: failed to create image wall (wall.png)\n", 2);
	game->images.empty = mlx_texture_to_image(game->mlx, game->textures.empty);
	if (!game->images.empty)
		ft_putstr_fd("Error: failed to create image empty (floor.png)\n", 2);
	game->images.collectible
		= mlx_texture_to_image(game->mlx, game->textures.collectible);
	if (!game->images.collectible)
		ft_putstr_fd("Error: failed to create image (collectible.png)\n", 2);
	game->images.exit = mlx_texture_to_image(game->mlx, game->textures.exit);
	if (!game->images.exit)
		ft_putstr_fd("Error: failed to create image exit (exit.png)\n", 2);
	game->images.player
		= mlx_texture_to_image(game->mlx, game->textures.player);
	if (!game->images.player)
		ft_putstr_fd("Error: failed to create image player (player.png)\n", 2);
	if (!game->images.wall || !game->images.empty || !game->images.collectible
		|| !game->images.exit || !game->images.player)
	{
		ft_putstr_fd("Error: Unable to create images\n", 2);
		free_images(game);
		return (0);
	}
	return (1);
}

void	free_images(t_game *game)
{
	if (game->images.wall)
	{
		mlx_delete_image(game->mlx, game->images.wall);
	}
	if (game->images.empty)
	{
		mlx_delete_image(game->mlx, game->images.empty);
	}
	if (game->images.collectible)
	{
		mlx_delete_image(game->mlx, game->images.collectible);
	}
	if (game->images.exit)
	{
		mlx_delete_image(game->mlx, game->images.exit);
	}
	if (game->images.player)
	{
		mlx_delete_image(game->mlx, game->images.player);
	}
}
