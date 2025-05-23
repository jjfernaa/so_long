/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 00:35:31 by juan-jof          #+#    #+#             */
/*   Updated: 2025/05/23 19:39:47 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	validate_args(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd (ERR_ARGS, 2);
		return (0);
	}
	if (!check_file_extension(argv[1], ".ber"))
	{
		ft_putstr_fd(ERR_EXTENSION, 2);
		return (0);
	}
	return (1);
}

static int	setup_game(t_game *game, char *map_path)
{
	if (!parse_map(game, map_path) || !check_map_validity(game))
	{
		free_game(game);
		return (0);
	}
	if (!init_window(game) || !load_textures(game)
		|| !create_images(game))
	{
		clean_exit(game);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (!validate_args(argc, argv))
		return (1);
	game = init_game();
	if (!game)
	{
		ft_putstr_fd(ERR_MEMORY, 2);
		return (1);
	}
	if (!setup_game(game, argv[1]))
		return (1);
	render_map(game);
	mlx_key_hook(game->mlx, &hook_keys, game);
	mlx_loop(game->mlx);
	mlx_close_hook(game->mlx, handle_close, game);
	mlx_terminate(game->mlx);
	free_textures(&game->textures);
	free_game(game);
	return (0);
}
