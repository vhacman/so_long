/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:04:04 by vhacman           #+#    #+#             */
/*   Updated: 2025/04/11 14:04:04 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*
 * Loads the wall image from an XPM file.
 * - File path is "src/textures/wall.xpm".
 * - Validates the extension to ensure it is a .xpm file.
 * - Uses mlx_xpm_file_to_image() to load the image.
 * - Stores the result in game->img_wall.
 * - Exits with an error message if loading fails.
 */
void	load_wall(t_game *game)
{
	int			img_width;
	int			img_height;
	const char	*wall_path = "so_long_bonus/src/textures/wall.xpm";

	if (!has_xpm_extension(wall_path))
		exit_with_error("file must have .xpm ext\n", game, 1);
	game->img_wall = mlx_xpm_file_to_image(game->mlx, (char *)wall_path,
			&img_width, &img_height);
	if (!game->img_wall)
		exit_with_error("Error\nfailed to load wall image\n", game, 1);
}

/*
 * Renders wall tiles at all positions marked '1' in the map.
 * - Iterates over the entire map grid.
 * - For each tile with value '1', draws the wall texture.
 * - Uses a fixed tile size of 64 pixels to compute screen coordinates.
 * - Calls mlx_put_image_to_window() for each wall tile.
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
