/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>         +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:00:00 by vhacman           #+#    #+#             */
/*   Updated: 2025/05/05 15:00:00 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*
** load_exit:
** - Loads the exit tile image from the path specified by EXIT_TEXTURE_PATH.
**
** Steps:
** 1. Checks that the file extension is ".xpm" using has_xpm_extension.
** 2. Loads the image using mlx_xpm_file_to_image:
**     - Stores the image pointer in game->img_exit.
**     - Retrieves image dimensions but does not store them.
** 3. If the image fails to load (returns NULL), exits with an error.
**
** Purpose:
** - Prepares the static graphic used to represent the level exit ('E') tile.
*/
void	load_exit(t_game *game)
{
	int			img_width;
	int			img_height;
	const char	*exit_path;

	exit_path = EXIT_TEXTURE_PATH;
	if (!has_xpm_extension(exit_path))
		exit_with_error("file must have .xpm ext\n", game, 1);
	game->img_exit = mlx_xpm_file_to_image(game->mlx, (char *)exit_path,
			&img_width, &img_height);
	if (!game->img_exit)
		exit_with_error("Error\nFailed to upload exit\n", game, 1);
}

/*
** draw_exit:
** - Draws the exit tile on the screen at the position marked 'E' in the map.
**
** Steps:
** 1. Iterates over the entire map grid (rows and columns).
** 2. When the 'E' tile is found:
**     - Converts its grid coordinates to pixel coordinates (×64).
**     - Draws the exit image using mlx_put_image_to_window.
**     - Exits immediately after drawing the first exit tile.
**
** Assumptions:
** - There is exactly one 'E' tile in the map (enforced during validation).
** - game->img_exit has been successfully loaded before this call.
*/
void	draw_exit(t_game *game)
{
	int	tile_size;
	int	x;
	int	y;

	tile_size = 64;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'E')
			{
				mlx_put_image_to_window(game->mlx, game->window,
					game->img_exit, x * tile_size, y * tile_size);
				return ;
			}
			x++;
		}
		y++;
	}
}
