/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:43:10 by vhacman           #+#    #+#             */
/*   Updated: 2025/05/08 11:43:10 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * Releases the MiniLibX graphical context.
 * - Destroys the window if both game->mlx and game->window are valid.
 * - Resets game->window to NULL to prevent use-after-free.
 * - Destroys the display context and frees the MLX pointer.
 * - Sets game->mlx to NULL to clean dangling memory references.
 * - Required to properly shut down the MLX system without leaks.
 */
static void	free_mlx_context(t_game *game)
{
	if (game->mlx && game->window)
	{
		mlx_destroy_window(game->mlx, game->window);
		game->window = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

/*
 * Frees all mandatory graphical assets used by the game.
 * - Calls free_static_images() to destroy loaded textures such as
 *   player, walls, exit, background, etc.
 * - Calls null_all_images() to reset all image pointers to NULL.
 * - Calls free_mlx_context() to release the MLX window and context.
 */
static void	free_graphics(t_game *game)
{
	free_static_images(game);
	null_all_images(game);
	free_mlx_context(game);
}

/*
 * Frees the memory allocated for the game map.
 * - Iterates over each row of the map (char **) and frees it.
 * - Frees the map array itself after rows are released.
 * - Only called if game->map exists to avoid invalid memory access.
 */
void	free_map_data(t_game *game)
{
	int	i;

	if (game->map)
	{
		i = 0;
		while (i < game->map_height)
			free(game->map[i++]);
		free(game->map);
	}
}

/*
 * Main cleanup routine for the entire program.
 * - Called on normal exit or error.
 * - Frees all graphical assets and the game map.
 * - Ensures no memory leaks or dangling pointers remain.
 */
void	cleanup(t_game *game)
{
	free_static_images(game);
	free_graphics(game);
	free_map_data(game);
}
