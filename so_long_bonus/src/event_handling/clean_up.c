/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:43:10 by vhacman           #+#    #+#             */
/*   Updated: 2025/05/03 11:43:10 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/* 
 * Releases all MiniLibX resources and the game window.
 * If both mlx context and window exist, destroys the window.
 * Destroys the display, frees the mlx pointer, and nullifies it
 * to prevent memory leaks or access to freed memory.
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
 * Frees all graphical assets used in the game.
 * Releases static images (e.g. walls, floor).
 * Releases animated images (e.g. player, enemy).
 * Resets all image pointers to NULL to avoid invalid access.
 * Finally, releases the mlx context via free_mlx_context().
 */
static void	free_graphics(t_game *game)
{
	free_static_images(game);
	free_animated_images(game);
	null_all_images(game);
	free_mlx_context(game);
}

/* 
 * Frees the map and related pathfinding memory.
 * Frees each row of the 2D map array, then the map itself.
 * Frees the dynamically allocated enemy_path array.
 * Frees the visited matrix used for pathfinding or validation.
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
	if (game->enemy_path)
		free(game->enemy_path);
	if (game->visited)
	{
		i = 0;
		while (i < game->map_height)
			free(game->visited[i++]);
		free(game->visited);
	}
}

/* 
 * Main cleanup function called at exit or on error.
 * - Frees all graphical resources by calling free_graphics().
 * - Frees map data and related memory via free_map_data().
 * Ensures no memory leaks by deallocating all used resources.
 */
void	cleanup(t_game *game)
{
	free_graphics(game);
	free_map_data(game);
}
