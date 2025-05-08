/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>         +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:00:00 by vhacman           #+#    #+#             */
/*   Updated: 2025/04/11 15:00:00 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * Loads the exit tile image from file into the game structure.
 * - The file path is defined by the macro EXIT_TEXTURE_PATH.
 * - Verifies that the file has a ".xpm" extension using has_xpm_extension().
 * - Uses mlx_xpm_file_to_image() to load the image into memory.
 *   → Requires width and height pointers even if not stored.
 * - If loading fails, calls exit_with_error() and terminates the program.
 * - The loaded image is stored in game->img_exit and used later in rendering.
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
 * Draws the exit image at the location of the 'E' tile in the map.
 * - Assumes a tile size of 64 pixels.
 * - Iterates over the 2D map array looking for the first occurrence of 'E'.
 * - When found, calculates pixel position by multiplying tile index by 64.
 * - Draws game->img_exit using mlx_put_image_to_window().
 * - Returns immediately after placing the first exit image.
 * - Assumes only one 'E' exists; multiple exits are not supported here.
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
