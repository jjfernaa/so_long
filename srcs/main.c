/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 00:35:31 by juan-jof          #+#    #+#             */
/*   Updated: 2025/05/14 02:58:52 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	validate_args(int argc, char **argv, t_game **game)
{
	if (argc != 2)
	{
		ft_putstr_fd (ERR_ARGS, 2);
		return (0);
	}
	if (!check_file_extensione(argv[1], ".ber"))
	{
		ft_putstr_fd(ERR_EXTENSION, 2);
		return (0);
	}
	game = init_game();
	if (!game)
	{
		ft_putstr_fd(ERR_MEMORY, 2);
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
	if (!init_window(game) || !load_textures(game) \
		|| !create_map_validity(game))
	{
		clean_exit(game);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (!validate_args(argc, argv, &game))
		return (1);
	if (!setup_game(game, argv[1]))
		return (1);
	render_map(game);
	mlx_key_hook(game->mlx, &hook_keys, game);
	mlx_loop(game->mlx);
	clean_exit(game);
	return (0);
}
