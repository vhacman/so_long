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
** load_wall:
** - Loads the wall tile texture used to represent impassable areas.
** - Validates that the file path has a ".xpm" extension using has_xpm_extension.
** - Loads the image from "so_long_bonus/src/textures/wall.xpm" using
**   mlx_xpm_file_to_image, which returns a pointer to the loaded image.
** - Stores the resulting image in game->img_wall.
** - Retrieves the image’s width and height but does not store them.
** - If the image fails to load (returns NULL), the program exits with an error.
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
** draw_walls:
** - Renders the wall image on all tiles in the map marked with '1'.
** - Iterates through each row (y) and each column (x) of the map.
** - For each '1' tile, computes its screen position by multiplying
**   the tile's grid coordinates by the tile size (64 pixels).
** - Calls mlx_put_image_to_window to draw the wall image at the correct
**   position in the game window.
** - Ensures that all walls are visually rendered in their correct locations.
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
