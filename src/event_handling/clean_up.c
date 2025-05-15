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
** free_mlx_context:
** - Releases all MLX-related resources tied to the window and display.
** - If both game->mlx and game->window are valid:
**     - Destroys the window using mlx_destroy_window.
**     - Sets game->window to NULL to avoid dangling pointer.
** - If game->mlx is valid:
**     - Destroys the display context using mlx_destroy_display.
**     - Frees the MLX connection pointer.
**     - Sets game->mlx to NULL for safety.
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
** - Frees all loaded graphical assets and resets internal pointers.
** - Calls free_static_images to destroy all loaded XPM images.
** - Calls null_all_images to explicitly set all image pointers to NULL.
** - Calls free_mlx_context to close and free the MLX graphical context.
** - Ensures all graphical memory and window handles are released.
*/
static void	free_graphics(t_game *game)
{
	free_static_images(game);
	null_all_images(game);
	free_mlx_context(game);
}

/*
** free_map_data:
** - Frees all memory allocated for the map (game->map).
** - Iterates through each row of the 2D map array and frees it.
** - Then frees the main map pointer.
** - Protected by a check to ensure game->map is not NULL.
** - Avoids memory leaks from dynamically loaded map data.
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
** cleanup:
** - Top-level cleanup function called before exiting the program.
** - Frees all graphics, textures, MLX handles, and the map.
** - Delegates to free_graphics and free_map_data for modular cleanup.
** - Ensures clean shutdown of all allocated resources.
*/
void	cleanup(t_game *game)
{
	free_graphics(game);
	free_map_data(game);
}
