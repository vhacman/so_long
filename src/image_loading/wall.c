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
** Loads the wall texture from an XPM file to be used as the visual
** representation of walls in the game map.
** - Validates the file extension is ".xpm" using has_xpm_extension().
** - Uses mlx_xpm_file_to_image() to load the texture and assigns it
**   to `img_wall` in the game structure.
** - Image width and height are retrieved but not used here.
** - If loading fails, the program exits via exit_with_error().
** - The image is intended to be drawn on map tiles marked with '1'.
**
** Parameters:
** - game: pointer to the game structure where the wall texture is stored.
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
** draw_walls:
** - Iterates over each tile of the game map.
** - For every cell containing '1' (wall), draws the wall texture
**   at screen position (x * 64, y * 64) using mlx_put_image_to_window.
**   (Draw the wall image at the screen position corresponding to tile 
**    (x, y), which is located x * 64 pixels from the left and y * 64 
**    pixels from the top)
**
** - Uses game->img_wall as the source image.
** - Requires game->map, game->map_width, and game->map_height
**   to be properly initialized.
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
