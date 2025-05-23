/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 00:35:26 by juan-jof          #+#    #+#             */
/*   Updated: 2025/05/23 19:52:09 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_map(&game->map);
	free(game);
}

void	clean_exit(t_game *game)
{
	if (!game)
		exit(1);
	if (game->mlx)
	{
		if (game->images.wall)
			mlx_delete_image(game->mlx, game->images.wall);
		if (game->images.empty)
			mlx_delete_image(game->mlx, game->images.empty);
		if (game->images.collectible)
			mlx_delete_image(game->mlx, game->images.collectible);
		if (game->images.exit)
			mlx_delete_image(game->mlx, game->images.exit);
		if (game->images.player)
			mlx_delete_image(game->mlx, game->images.player);
		free_textures(&game->textures);
		mlx_terminate(game->mlx);
	}
	free_map(&game->map);
	free(game);
	exit (1);
}

void	print_error(char *error_message)
{
	ft_putstr_fd(error_message, 2);
}

void	handle_close(void *param)
{
	clean_exit((t_game *)param);
}
