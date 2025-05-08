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
 * Loads the exit tile image from an XPM file.
 * - The path is defined by EXIT_TEXTURE_PATH.
 * - Verifies the file has a .xpm extension.
 * - Loads the image into game->img_exit using mlx_xpm_file_to_image().
 * - Image dimensions are required by MLX but not stored.
 * - Exits with an error message if the image fails to load.
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
 * Renders the exit image at its location on the map.
 * - Uses a fixed tile size of 64 pixels for screen positioning.
 * - Iterates through the map to find the tile labeled 'E'.
 * - Draws game->img_exit at the corresponding screen coordinates.
 * - Assumes there is only one exit and exits the loop after drawing.
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
