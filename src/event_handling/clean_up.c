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
** Releases MLX graphical context and window resources.
** - If both `mlx` and `window` are valid,
** destroys the window and sets it to NULL.
** - Destroys the display context and frees the `mlx` pointer.
** - Sets `mlx` to NULL to avoid dangling references.
**
** Parameters:
** - game: pointer to the game structure containing MLX handles.
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
** Frees all graphical assets and resets associated pointers.
** - Destroys static images (sprites, backgrounds, screens, etc.).
** - Sets image pointers to NULL using null_all_images().
** - Destroys the MLX window and context using free_mlx_context().
**
** Parameters:
** - game: pointer to the game structure containing image and MLX data.
*/
static void	free_graphics(t_game *game)
{
	free_static_images(game);
	null_all_images(game);
	free_mlx_context(game);
}

/*
** Frees the dynamically allocated memory for the game map.
** - Iterates through each map row and frees it.
** - Frees the entire map array after all rows are released.
** - Safeguarded by checking if `game->map` is non-null.
**
** Parameters:
** - game: pointer to the game structure containing the map.
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
** Performs a complete cleanup of the game's allocated resources.
** - Frees graphics, textures, MLX context, and map data.
** - Should be called before any program exit to ensure clean shutdown.
**
** Parameters:
** - game: pointer to the game structure with all allocated resources.
*/
void	cleanup(t_game *game)
{
	free_graphics(game);
	free_map_data(game);
}
