/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:04:04 by vhacman           #+#    #+#             */
/*   Updated: 2025/05/06 11:23:00 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * Loads the wall texture used to render the solid boundaries in the map.
 * - Expects the file "src/textures/wall.xpm" to be present and valid.
 * - Validates that the file has a ".xpm" extension with has_xpm_extension().
 * - Uses mlx_xpm_file_to_image() to load the image into game->img_wall.
 *   → Also retrieves the image width and height (unused here).
 * - If the image fails to load, prints an error and exits the program.
 * - This image will be drawn on every tile marked '1' in the map.
 */
void	load_wall(t_game *game)
{
	int			img_width;
	int			img_height;
	const char	*wall_path = "src/textures/wall.xpm";

	if (!has_xpm_extension(wall_path))
		exit_with_error("file must have .xpm ext\n", game, 1);
	game->img_wall = mlx_xpm_file_to_image(game->mlx, (char *)wall_path,
			&img_width, &img_height);
	if (!game->img_wall)
		exit_with_error("Error\nfailed to load wall image\n", game, 1);
}

/*
 * Draws the wall image on every map tile containing '1'.
 * - Assumes tile size of 64 pixels.
 * - Iterates through all map rows (y) and columns (x).
 * - For each tile, checks if it equals '1' (wall).
 * - If yes, calculates its pixel position: (x * 64, y * 64).
 * - Calls mlx_put_image_to_window() to draw game->img_wall at that position.
 * - Repeats until all wall tiles are rendered.
 */
void	draw_walls(t_game *game)
{
	int	x;
	int	y;
	int	tile_size;

	tile_size = 64;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == '1')
			{
				mlx_put_image_to_window(game->mlx, game->window,
					game->img_wall, x * tile_size, y * tile_size);
			}
			x++;
		}
		y++;
	}
}
