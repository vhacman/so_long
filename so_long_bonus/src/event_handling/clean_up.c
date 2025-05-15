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
 ** free_mlx_context:
 ** Releases all MiniLibX graphical resources and the game window.
 ** If both mlx context and window exist:
 **   - Destroys the window to free OS resources.
 **   - Sets game->window to NULL to prevent invalid access.
 ** Destroys the display connection and frees the mlx pointer.
 ** Sets game->mlx to NULL to avoid dangling pointer usage.
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
 ** free_graphics:
 ** Frees all loaded graphical assets used in the game.
 ** Calls functions to free static images like walls, floor, exit.
 ** Calls functions to free animated images like player and enemy sprites.
 ** Resets all image pointers in game struct to NULL to avoid invalid use.
 ** Finally, calls free_mlx_context() to properly release MLX context.
 */
static void	free_graphics(t_game *game)
{
	free_static_images(game);
	free_animated_images(game);
	null_all_images(game);
	free_mlx_context(game);
}

/*
 ** free_map_data:
 ** Frees all dynamic memory related to the game map and paths.
 ** Frees each row of game->map, then frees the map array.
 ** Frees enemy_path array if allocated.
 ** Frees visited matrix rows and then the matrix pointer.
 ** Ensures no memory leaks from map and pathfinding data.
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
 ** cleanup:
 ** Main cleanup function called on exit or error.
 ** Calls free_graphics to free all image and MLX resources.
 ** Calls free_map_data to free map and pathfinding memory.
 ** Ensures all allocated memory and resources are freed.
 */
void	cleanup(t_game *game)
{
	free_graphics(game);
	free_map_data(game);
}
